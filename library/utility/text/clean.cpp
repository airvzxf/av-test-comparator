#include "trim.h"
#include "escape.h"
#include "clean.h"

namespace library::utility::text {
    std::string clean(std::string text) {
        std::string trimText = trim(text);
        return escapeCharacters(trimText);
    }
}
