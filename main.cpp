#include <vector>
#include "core/core.h"

int main() {
    // TODO: Fix the error (added remove tag TD rather than extract) -> Error: Not found the first ELEMENT -> -|<td|-.
    auto *settings = core::structure::settings::getInstance();
    settings->error.display = true;
    settings->debug.display = true;

    const std::string mainUrl = "https://www.av-test.org/en/antivirus/home-windows/windows-10/";

    std::vector<std::string> urls;
    urls.emplace_back(mainUrl + "august-2020");
//    urls.emplace_back(mainUrl + "june-2020");
//    urls.emplace_back(mainUrl + "april-2020");

    std::vector<core::structure::antivirus> &toCatalog = core::structure::catalog;
    toCatalog.reserve(32);

    for (std::string &url : urls) {
        core::windows::pc::main::setInformationFrom(url + "/", toCatalog);
    }

    return 0;
}
