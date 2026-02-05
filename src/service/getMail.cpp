#include <curl/curl.h>
#include <string>
#include <iostream>

// buffer (idk what this does tbh)
static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    auto *out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
};

// todo replace demo
std::string fetch_latest_email_raw(const std::string &server, const std::string &user, const std::string &pass) {
    CURL *curl = curl_easy_init();
    std::string response;

    curl_easy_setopt(curl, CURLOPT_USERNAME, user.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, pass.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, server.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "FETCH 2:* (BODY[HEADER.FIELDS (SUBJECT FROM DATE)])");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return response;
};

// todo replace demo
std::string extract_field(const std::string &src, const std::string &field) {
    auto pos = src.rfind(field);
    if (pos == std::string::npos) return "";

    auto start = pos + field.size();
    auto end = src.find("\r\n", start);
    if (end == std::string::npos) {
        end = src.find('\n', start);
    };
    if (end == std::string::npos) {
        end = src.size();
    };

    return src.substr(start, end - start);
};
