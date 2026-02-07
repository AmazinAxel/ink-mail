#include <curl/curl.h>
#include <string>
#include "../app.hpp"

// Curl write callback
static size_t writeCb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
};

bool markEmailAsRead(const std::string& imap, const std::string& email, const std::string& password, int uid) {
    CURL* curl = curl_easy_init();

    std::string response;
    std::string request = "UID STORE " + std::to_string(uid) + " +FLAGS (\\Seen)";

    curl_easy_setopt(curl, CURLOPT_URL, imap.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, email.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK);
};
