#ifndef AV_TEST_COMPARATOR_LIBRARY_HTML_EXTRACT_TAG_H
#define AV_TEST_COMPARATOR_LIBRARY_HTML_EXTRACT_TAG_H

#include <string>

namespace library::html::extract::tag {
    std::string getTableFrom(std::string &htmlCode);

    std::string getTrFrom(std::string &htmlCode);

    std::string getTdFrom(std::string &htmlCode);

}
#endif //AV_TEST_COMPARATOR_LIBRARY_HTML_EXTRACT_TAG_H
