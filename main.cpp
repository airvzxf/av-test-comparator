#include <iostream>
#include <curl/curl.h>

static size_t writeCallback(void *contents, size_t size, size_t memoryBytes, void *userData) {
    ((std::string *) userData)->append((char *) contents, size * memoryBytes);
    return size * memoryBytes;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string errorMessage;
    const char *userAgent = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0";

    CURL *curl;
    CURLcode res = CURL_LAST;
    std::string readBuffer;

    curl = curl_easy_init();
    if (!curl) {
        errorMessage = "CURL Error: ";
        errorMessage += curl_easy_strerror(res);
        throw std::runtime_error(errorMessage.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://rovisoft.net/");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        errorMessage = "CURL Error: ";
        errorMessage += curl_easy_strerror(res);
        throw std::runtime_error(errorMessage.c_str());
    }

    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;

    return 0;
}
