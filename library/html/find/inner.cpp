#include "inner.h"
#include "../../library.h"

namespace library::html::find::inner {
    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt) {
        std::string extraction;

        if (text.empty())
            return extraction;

        std::size_t firstPosition = library::utility::text::findFrom(text, startAt, 0, false);
        if (firstPosition == std::string::npos)
            return extraction;

        std::size_t lastPosition = library::utility::text::findFrom(text, endAt, firstPosition, true);
        if (lastPosition == std::string::npos)
            return extraction;

        std::size_t size = lastPosition - firstPosition;
        extraction = text.substr(firstPosition, size);

        return extraction;
    }
}
