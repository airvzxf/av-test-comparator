#ifndef AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_TRIM_H
#define AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_TRIM_H

#include <string>

namespace library::utility::text {
    std::string &leftTrim(std::string &text, const std::string &chars);

    std::string &rightTrim(std::string &text, const std::string &chars);

    std::string &trim(std::string &text, const std::string &chars);

    std::string &trim(std::string &text);
}
#endif //AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_TRIM_H
