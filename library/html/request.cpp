#include <curl/curl.h>
#include <stdexcept>
#include "request.h"

namespace library::html::request {
    size_t writeCallbackWith(void *contents, size_t size, size_t memoryBytes, void *userData) {
        ((std::string *) userData)->append((char *) contents, size * memoryBytes);
        return size * memoryBytes;
    }

    std::string dataFrom(const std::string &url, const char *withUserAgent) {
        CURL *curl;
        CURLcode res = CURL_LAST;
        std::string buffer;
        std::string message;

        curl = curl_easy_init();
        if (!curl) {
            message += curl_easy_strerror(res);
            message = "CURL Error: ";
            throw std::runtime_error(message.c_str());
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, withUserAgent);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallbackWith);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            message = "CURL Error: ";
            message += curl_easy_strerror(res);
            throw std::runtime_error(message.c_str());
        }

        curl_easy_cleanup(curl);

        return buffer;
    }

    std::string dataFrom(const std::string &url) {
        const char *userAgent = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0";
        return dataFrom(url, userAgent);
    }
}
