#include "inner.h"

namespace library::html::extract::inner {
    std::string getHtmlInnerFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag) {
        std::string tagContent;

        if (htmlCode.empty())
            return tagContent;

        std::size_t firstPosition = htmlCode.find(firstTag);
        if (firstPosition == std::string::npos)
            return tagContent;

        std::size_t innerPosition = firstPosition + firstTag.size();
        std::size_t lastPosition = htmlCode.find(lastTag, innerPosition);
        if (lastPosition == std::string::npos)
            return tagContent;

        std::size_t size = lastPosition - innerPosition;
        tagContent = htmlCode.substr(innerPosition, size);

        return tagContent;
    }
}
