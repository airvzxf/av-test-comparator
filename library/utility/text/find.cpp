#include "find.h"

namespace library::utility::text {
    size_t findFrom(std::string &text, std::string withMatch, size_t startAt, bool inner) {
        bool found;
        size_t position = std::string::npos;
        char &first = withMatch[0];

        for (size_t i = startAt; i < text.length(); ++i) {
            char &character = text[i];
            if (character == first) {
                found = true;
                for (int j = 1; j < withMatch.length(); ++j) {
                    if (text[i + j] != withMatch[j]) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    position = i;
                    if (!inner)
                        position += withMatch.length();
                    break;
                }
            }
        }

        return position;
    }

    size_t findFrom(std::string &text, std::string withMatch) {
        return findFrom(text, std::move(withMatch), 0, true);
    }
}
