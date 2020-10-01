#include <iostream>
#include "outer.h"

namespace library::html::extract::outer {
    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt, bool erase,
                            bool displayError) {
        std::string extraction;

        if (text.empty())
            return extraction;

        std::size_t firstPosition = text.find(startAt);
        if (firstPosition == std::string::npos) {
            if (displayError)
                std::cerr << "Error: Not found the first HTML tag -> " << startAt << "." << std::endl;
            return extraction;
        }

        std::size_t lastPosition = text.find(endAt, firstPosition + startAt.size());
        if (lastPosition == std::string::npos) {
            if (displayError)
                std::cerr << "Error: Not found the last HTML tag -> " << endAt << "." << std::endl;
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

    std::string getTextFrom(std::string &text, const std::string &startAt, const std::string &endAt) {
        return getTextFrom(text, startAt, endAt, false, false);
    }
}
