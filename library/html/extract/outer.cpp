#include <iostream>
#include "outer.h"
#include "../../../core/structure/settings.h"

namespace library::html::extract::outer {
    std::string
    getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt, bool erase) {
        std::string extraction;

        if (text.empty())
            return extraction;

        std::size_t firstPosition = text.find(startAt);
        if (firstPosition == std::string::npos) {
            if (core::structure::settings::getInstance()->error.display)
                std::cerr << "Error: Not found the first ELEMENT -> -|" << startAt << "|-." << std::endl;
            return extraction;
        }

        std::size_t lastPosition = text.find(endAt, firstPosition + startAt.size());
        if (lastPosition == std::string::npos) {
            if (core::structure::settings::getInstance()->error.display)
                std::cerr << "Error: Not found the last ELEMENT -> -|" << endAt << "|-." << std::endl;
            return extraction;
        }

        std::size_t size = lastPosition - firstPosition + endAt.size();
        extraction = text.substr(firstPosition, size);

        if (erase) {
            const std::string firstCode = text.substr(0, firstPosition);
            const std::string lastCode = text.substr(lastPosition + endAt.size());
            text = firstCode + lastCode;
        }

        return extraction;
    }
}
