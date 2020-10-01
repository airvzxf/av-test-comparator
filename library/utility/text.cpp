#include "text.h"

namespace library::utility::text {
    std::string &leftTrim(std::string &text, const std::string &chars) {
        text.erase(0, text.find_first_not_of(chars));
        return text;
    }

    std::string &rightTrim(std::string &text, const std::string &chars) {
        text.erase(text.find_last_not_of(chars) + 1);
        return text;
    }

    std::string &trim(std::string &text, const std::string &chars) {
        return leftTrim(rightTrim(text, chars), chars);
    }

    std::string &trim(std::string &text) {
        const std::string spaces = "\t\n\v\f\r ";
        return trim(rightTrim(text, spaces), spaces);
    }
}
