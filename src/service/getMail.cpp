#include <curl/curl.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <map>
#include "../app.hpp"

static size_t writeCb(char *ptr, size_t size, size_t nmemb, void *userdata) {
    auto *out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
}

static std::string extractField(const std::string &src, const std::string &field) {
    size_t pos = src.find(field);
    if (pos == std::string::npos) return "";

    size_t start = pos + field.size();
    size_t end = src.find("\r\n", start);
    if (end == std::string::npos)
        end = src.find("\n", start);
    if (end == std::string::npos)
        end = src.size();

    return src.substr(start, end - start);
}

static std::vector<std::pair<int,std::string>> parseFetchBlocks(const std::string &raw) {
    std::vector<std::pair<int,std::string>> out;

    size_t i = 0;
    while (true) {
        size_t star = raw.find("* ", i);
        if (star == std::string::npos) break;

        size_t fetch = raw.find("FETCH", star);
        if (fetch == std::string::npos) break;

        // Extract UID
        size_t uidPos = raw.find("UID ", fetch);
        if (uidPos == std::string::npos) break;

        uidPos += 4;
        int uid = std::stoi(raw.substr(uidPos));

        // Find next "* " to mark end of this block
        size_t next = raw.find("\n* ", star + 1);
        if (next == std::string::npos)
            next = raw.size();

        std::string block = raw.substr(star, next - star);
        out.push_back({uid, block});

        i = next;
    };

    return out;
};

static std::string extractLiteral(const std::string &block) {
    // Look for {1234}
    size_t brace = block.find('{');
    if (brace == std::string::npos) return "";

    size_t endBrace = block.find('}', brace);
    if (endBrace == std::string::npos) return "";

    int len = std::stoi(block.substr(brace + 1, endBrace - brace - 1));

    // Literal starts after CRLF following the brace
    size_t start = block.find("\r\n", endBrace);
    if (start == std::string::npos)
        start = block.find("\n", endBrace);
    if (start == std::string::npos)
        return "";

    start += 2; // skip CRLF

    if (start + len > block.size())
        return block.substr(start); // truncated but safe

    return block.substr(start, len);
};

std::vector<int> fetchUIDs(const std::string &imap, const std::string &email, const std::string &password) {
    CURL *curl = curl_easy_init();
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

    std::vector<int> uids;

    size_t pos = response.find("SEARCH");
    if (pos == std::string::npos) return uids;

    std::stringstream ss(response.substr(pos + 6));
    int uid;
    while (ss >> uid)
        uids.push_back(uid);

    return uids;
}

std::vector<emailData> fetchMail(const std::string &imap, const std::string &email, const std::string &password) {
    auto uids = fetchUIDs(imap, email, password);
    if (uids.empty()) return {};

    if (uids.size() > 30)
        uids.erase(uids.begin(), uids.end() - 30);

    // Build UID list
    std::string uidList;
    for (size_t i = 0; i < uids.size(); i++) {
        uidList += std::to_string(uids[i]);
        if (i + 1 < uids.size()) uidList += ",";
    }

    CURL *curl = curl_easy_init();
    std::string headerResponse;

    std::string headerCmd = "UID FETCH " + uidList + " (BODY.PEEK[HEADER.FIELDS (SUBJECT FROM DATE)])";

    curl_easy_setopt(curl, CURLOPT_URL, imap.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, email.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, headerCmd.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &headerResponse);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    auto headerBlocks = parseFetchBlocks(headerResponse);

    // Map UID → emailData
    std::map<int,emailData> emails;

    for (auto &p : headerBlocks) {
        int uid = p.first;
        const std::string &block = p.second;

        emailData e;
        e.vbox = nullptr;

        std::string literal = extractLiteral(block);

        e.subject  = extractField(literal, "Subject: ");
        e.from     = extractField(literal, "From: ");
        e.sendDate = extractField(literal, "Date: ");

        emails[uid] = e;
    };

    for (int uid : uids) {
        CURL *curl2 = curl_easy_init();
        std::string bodyResponse;

        std::string bodyCmd = "UID FETCH " + std::to_string(uid) + " (BODY.PEEK[TEXT])";

        curl_easy_setopt(curl2, CURLOPT_URL, imap.c_str());
        curl_easy_setopt(curl2, CURLOPT_USERNAME, email.c_str());
        curl_easy_setopt(curl2, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl2, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        curl_easy_setopt(curl2, CURLOPT_CUSTOMREQUEST, bodyCmd.c_str());
        curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, writeCb);
        curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &bodyResponse);

        curl_easy_perform(curl2);
        curl_easy_cleanup(curl2);

        auto blocks = parseFetchBlocks(bodyResponse);
        if (!blocks.empty()) {
            std::string literal = extractLiteral(blocks[0].second);
            emails[uid].message = literal;
        };
    };

    std::vector<emailData> out;
    out.reserve(uids.size());
    for (int uid : uids)
        out.push_back(emails[uid]);

    return out;
};
