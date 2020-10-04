#ifndef AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_FIND_H
#define AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_FIND_H

#include <string>

namespace library::utility::text {
    size_t findFrom(std::string &text, std::string withMatch);

    size_t findFrom(std::string &text, std::string withMatch, size_t startAt, bool inner);
}
#endif //AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_FIND_H
