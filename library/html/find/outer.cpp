#include "outer.h"
#include "../extract/outer.h"

namespace library::html::find::outer {
    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt) {
        return library::html::extract::outer::getTextFrom(text, startAt, endAt, false, false);
    }
}
