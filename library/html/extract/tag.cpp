#include "tag.h"
#include "outer.h"

namespace library::html::extract::tag {
    std::string getTableFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<table", "</table>", true, false);
    }

    std::string getTrFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<tr", "</tr>", true, false);
    }

    std::string getTdFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<td", "</td>", true, false);
    }
}
