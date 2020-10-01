#include "replace.h"
#include "escape.h"

namespace library::utility::text {
    std::string escapeCharacters(std::string &text) {
        replace(text, std::string("&amp;"), std::string("&"));
        replace(text, std::string("&apos;"), std::string("'"));
        replace(text, std::string("&quot;"), std::string("\""));
        replace(text, std::string("&gt;"), std::string(">"));
        replace(text, std::string("&lt;"), std::string("<"));
        return text;
    }
}
