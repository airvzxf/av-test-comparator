#ifndef AV_TEST_COMPARATOR_LIBRARY_HTML_FIND_TAG_H
#define AV_TEST_COMPARATOR_LIBRARY_HTML_FIND_TAG_H

#include <string>

namespace library::html::find::tag {
    std::string getTableFrom(std::string &htmlCode);

    std::string getTbodyFrom(std::string &htmlCode);

    std::string getSpanFrom(std::string &htmlCode);

    std::string getStrongFrom(std::string &htmlCode);

    std::string getSrcFrom(std::string &htmlCode);

    std::string getDataLabelFrom(std::string &htmlCode);

    std::string getHrefFrom(std::string &htmlCode);
}
#endif //AV_TEST_COMPARATOR_LIBRARY_HTML_FIND_TAG_H
