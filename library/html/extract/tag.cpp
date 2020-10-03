#include "tag.h"
#include "outer.h"

namespace library::html::extract::tag {
    std::string getTableFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<table", "</table>", true);
    }

    std::string getTrFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<tr", "</tr>", true);
    }

    std::string getTdFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<td", "</td>", true);
    }
}
