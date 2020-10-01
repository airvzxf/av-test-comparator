#include <iostream>
#include "outer.h"

namespace library::html::extract::outer {
    std::string
    getHtmlTagFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag,
                   bool extract,
                   bool displayError) {
        std::string tagContent;

        if (htmlCode.empty())
            return tagContent;

        std::size_t firstPosition = htmlCode.find(firstTag);
        if (firstPosition == std::string::npos) {
            if (displayError)
                std::cerr << "Error: Not found the first HTML tag -> " << firstTag << "." << std::endl;
            return tagContent;
        }

        std::size_t lastPosition = htmlCode.find(lastTag, firstPosition + firstTag.size());
        if (lastPosition == std::string::npos) {
            if (displayError)
                std::cerr << "Error: Not found the last HTML tag -> " << lastTag << "." << std::endl;
            return tagContent;
        }

        std::size_t size = lastPosition - firstPosition + lastTag.size();
        tagContent = htmlCode.substr(firstPosition, size);

        if (extract) {
            const std::string firstCode = htmlCode.substr(0, firstPosition);
            const std::string lastCode = htmlCode.substr(lastPosition + lastTag.size());
            htmlCode = firstCode + lastCode;
        }

        return tagContent;
    }

    std::string getHtmlTagFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag) {
        return getHtmlTagFrom(htmlCode, firstTag, lastTag, false, false);
    }
}
