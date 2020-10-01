#ifndef AV_TEST_COMPARATOR_INNER_H
#define AV_TEST_COMPARATOR_INNER_H

#include <string>

namespace library::html::extract::inner {
    std::string getHtmlInnerFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag);
}
#endif //AV_TEST_COMPARATOR_INNER_H
