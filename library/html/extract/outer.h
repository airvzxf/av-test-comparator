#ifndef AV_TEST_COMPARATOR_OUTER_H
#define AV_TEST_COMPARATOR_OUTER_H

#include <string>

namespace library::html::extract::outer {
    std::string getHtmlTagFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag);

    std::string
    getHtmlTagFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag, bool extract,
                   bool displayError);
}
#endif //AV_TEST_COMPARATOR_OUTER_H
