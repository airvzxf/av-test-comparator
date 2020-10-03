#include "tag.h"
#include "inner.h"
#include "../extract/outer.h"
#include "outer.h"

namespace library::html::find::tag {
    std::string getTableFrom(std::string &htmlCode) {
        return library::html::find::outer::getTextFrom(htmlCode, "<table>", "</table>");
    }

    std::string getTbodyFrom(std::string &htmlCode) {
        return library::html::find::outer::getTextFrom(htmlCode, "<tbody>", "</tbody>");
    }

    std::string extractTrFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<tr", "</tr>", true, false);
    }

    std::string extractTdFrom(std::string &htmlCode) {
        return library::html::extract::outer::getTextFrom(htmlCode, "<td", "</td>", true, false);
    }

    std::string getStrongFrom(std::string &htmlCode) {
        return library::html::find::inner::getTextFrom(htmlCode, "<strong>", "</strong>");
    }

    std::string getSrcFrom(std::string &htmlCode) {
        return library::html::find::inner::getTextFrom(htmlCode, "src=\"", "\"");
    }

    std::string getDataLabelFrom(std::string &htmlCode) {
        return library::html::find::inner::getTextFrom(htmlCode, "data-label=\"", "\"");
    }

    std::string getHrefFrom(std::string &htmlCode) {
        return library::html::find::inner::getTextFrom(htmlCode, "href=\"", "\"");
    }
}
