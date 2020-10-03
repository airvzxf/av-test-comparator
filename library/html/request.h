#ifndef AV_TEST_COMPARATOR_LIBRARY_HTML_REQUEST_H
#define AV_TEST_COMPARATOR_LIBRARY_HTML_REQUEST_H

#include <string>

namespace library::html::request {
    size_t writeCallbackWith(void *contents, size_t size, size_t memoryBytes, void *userData);

    std::string getDataFrom(const std::string &url, const char *withUserAgent);

    std::string getDataFrom(const std::string &url);
}
#endif //AV_TEST_COMPARATOR_LIBRARY_HTML_REQUEST_H
