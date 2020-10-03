#ifndef AV_TEST_COMPARATOR_LIBRARY_HTML_EXTRACT_OUTER_H
#define AV_TEST_COMPARATOR_LIBRARY_HTML_EXTRACT_OUTER_H

#include <string>

namespace library::html::extract::outer {
    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt, bool remove);
}
#endif //AV_TEST_COMPARATOR_LIBRARY_HTML_EXTRACT_OUTER_H
