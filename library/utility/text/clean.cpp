#include "trim.h"
#include "escape.h"
#include "clean.h"

namespace library::utility::text {
    std::string clean(std::string text) {
        text = trim(text);
        return escapeCharacters(text);
    }
}
