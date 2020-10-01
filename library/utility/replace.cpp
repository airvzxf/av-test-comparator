#include "replace.h"

namespace library::utility::text {
    void replace(std::string &text, const std::string &old, const std::string &repl) {
        size_t pos = 0;
        while ((pos = text.find(old, pos)) != std::string::npos) {
            text.replace(pos, old.length(), repl);
            pos += repl.length();
        }
    }
}
