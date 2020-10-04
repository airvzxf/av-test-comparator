#include "replace.h"
#include "find.h"

namespace library::utility::text {
    void replace(std::string &text, const std::string &old, const std::string &repl) {
        size_t pos = 0;
        while ((pos = library::utility::text::findFrom(text, old, pos, true)) != std::string::npos) {
            text.replace(pos, old.length(), repl);
            pos += repl.length();
        }
    }
}
