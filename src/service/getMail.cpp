#include <curl/curl.h>
#include <string>
#include <thread>
#include <algorithm>
#include <vector>
#include <functional>
#include <sstream>
#include <gmime/gmime.h>
#include "../app.hpp"

// Curl write callback
static size_t writeCb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
};

// gmime get body plaintext helper
static std::string getPlaintext(GMimeObject* obj) {
    if (GMIME_IS_PART(obj)) {
        GMimeContentType* ct = g_mime_object_get_content_type(obj);
        if (g_mime_content_type_is_type(ct, "text", "plain")) {
            GMimePart* part = GMIME_PART(obj);
            GMimeDataWrapper* dw = g_mime_part_get_content(part);

            GMimeStream* mem = g_mime_stream_mem_new();
            g_mime_data_wrapper_write_to_stream(dw, mem);

            GMimeStreamMem* smem = GMIME_STREAM_MEM(mem);
            GByteArray* ba = g_mime_stream_mem_get_byte_array(smem);

            std::string out;
            if (ba && ba->data && ba->len)
                out.assign((char*)ba->data, ba->len);

            g_object_unref(mem);
            return out;
        };
    };
    if (GMIME_IS_MULTIPART(obj)) {
        GMimeMultipart* mp = GMIME_MULTIPART(obj);
        int n = g_mime_multipart_get_count(mp);
        for (int i = 0; i < n; i++) {
            std::string res = getPlaintext(g_mime_multipart_get_part(mp, i));
            if (!res.empty())
                return res;
        };
    };
    return {};
};

static std::string removeLinks(const std::string& s) {
    std::string out;
    out.reserve(s.size());

    bool inside = false;
    for (char c : s) {
        if (c == '<') { inside = true; continue; }
        if (c == '>') { inside = false; continue; }
        if (!inside) out.push_back(c);
    };
    return out;
};

static bool fetchSingleEmail(const std::string& imap, const std::string& email, const std::string& password, int uid, emailData& out) {
    CURL* curl = curl_easy_init();
    std::string response;
    std::string request = "UID FETCH " + std::to_string(uid) + " (FLAGS BODY.PEEK[])";

    curl_easy_setopt(curl, CURLOPT_URL, imap.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, email.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // Get literal length
    size_t brace = response.find('{');
    size_t endBrace = response.find('}', brace);
    int len = std::stoi(response.substr(brace + 1, endBrace - brace - 1));
    size_t start = response.find("\r\n", endBrace);
    if (start == std::string::npos)
        start = response.find("\n", endBrace);

    start += 2;

    if (start + len > response.size())
        return false;

    std::string literal = response.substr(start, len);

    // Gmime parse and save in var
    GMimeStream* stream = g_mime_stream_mem_new_with_buffer((const char*)literal.data(), literal.size());
    GMimeParser* parser = g_mime_parser_new_with_stream(stream);
    GMimeMessage* msg = g_mime_parser_construct_message(parser, NULL);

    if (!msg) {
        g_object_unref(parser);
        g_object_unref(stream);
        return false;
    };

    // Read/unread
    size_t flagsPos = response.find("FLAGS");
    if (flagsPos != std::string::npos) {
        size_t open = response.find('(', flagsPos);
        size_t close = response.find(')', open);
        if (open != std::string::npos && close != std::string::npos) {
            std::string flags = response.substr(open + 1, close - open - 1);
            if (flags.find("\\Seen") == std::string::npos)
                out.isRead = false;
            else
                out.isRead = true;
        };
    };

    // Message subject
    const char* subj = g_mime_message_get_subject(msg);
    if (subj) out.subject = subj;

    // Sender email
    InternetAddressList* list = g_mime_message_get_from(msg);
    if (list) out.from = internet_address_mailbox_get_addr(INTERNET_ADDRESS_MAILBOX(internet_address_list_get_address(list, 0)));

    // Formatted date & time
    GDateTime* dateTime = g_mime_message_get_date(msg);
    gchar* formattedSendDate = g_date_time_format(dateTime, "%a %b %-d, %Y at %H:%M");
    out.sendDate = formattedSendDate;
    g_free(formattedSendDate);

    // Body message
    GMimeObject* root = g_mime_message_get_mime_part(msg);
    out.message = removeLinks(getPlaintext(root));

    // Mail UID
    out.uid = uid;

    // Cleanup
    g_object_unref(msg);
    g_object_unref(parser);
    g_object_unref(stream);
    return true;
};

std::vector<emailData> fetchMail(const std::string& imap, const std::string& email, const std::string& password) {
    /* Get all the UIDs for each email for fetching */
    CURL* curl = curl_easy_init();
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, imap.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, email.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "UID SEARCH ALL");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    size_t pos = response.find("SEARCH");

    std::stringstream ss(response.substr(pos + 6));
    std::vector<int> uids;
    int uid;
    while (ss >> uid) uids.push_back(uid);

    if (uids.empty()) return emails; // No mail at all

    if (uids.size() > 10) // Hard cap mail at 10
        uids.erase(uids.begin(), uids.end() - 10);

    std::vector<int> newUIDs;
    for (int uid: uids)
        if (uid > currMailUID)
            newUIDs.push_back(uid);

    if (newUIDs.empty()) return emails; // No new mail

    for (int uid: newUIDs) {
        emailData mail {};
        fetchSingleEmail(imap, email, password, uid, mail);
        emails.insert(emails.begin(), mail);
    };

    currMailUID = newUIDs.front();
    return emails;
};

void fetchMailAsync(const std::string& imap, const std::string& email, const std::string& password, std::function<void()> onDone) {
    std::thread([=]() {
        fetchMail(imap, email, password); // updates global emails

        g_idle_add([](void* data) -> gboolean {
            auto* cb = static_cast<std::function<void()>*>(data);
            (*cb)();
            delete cb;
            return FALSE;
        }, new std::function<void()>(onDone));
    }).detach();
};
