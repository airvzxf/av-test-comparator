#include "inner.h"

namespace library::html::find::inner {
    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt) {
        std::string extraction;

        if (text.empty())
            return extraction;

        std::size_t firstPosition = text.find(startAt);
        if (firstPosition == std::string::npos)
            return extraction;

        std::size_t innerPosition = firstPosition + startAt.size();
        std::size_t lastPosition = text.find(endAt, innerPosition);
        if (lastPosition == std::string::npos)
            return extraction;

        std::size_t size = lastPosition - innerPosition;
        extraction = text.substr(innerPosition, size);

        return extraction;
    }
}
