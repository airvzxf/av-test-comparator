#ifndef AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_REPLACE_H
#define AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_REPLACE_H

#include <string>

namespace library::utility::text {
    void replace(std::string &text, const std::string &old, const std::string &repl);
}
#endif //AV_TEST_COMPARATOR_LIBRARY_UTILITY_TEXT_REPLACE_H
