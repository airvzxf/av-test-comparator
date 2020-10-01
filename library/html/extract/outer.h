#ifndef AV_TEST_COMPARATOR_OUTER_H
#define AV_TEST_COMPARATOR_OUTER_H

#include <string>

namespace library::html::extract::outer {
    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt);

    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt, bool remove,
                            bool displayError);
}
#endif //AV_TEST_COMPARATOR_OUTER_H
