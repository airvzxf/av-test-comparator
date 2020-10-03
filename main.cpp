#include <vector>
#include "core/core.h"

int main() {
    auto *settings = core::structure::settings::getInstance();
    settings->error.display = true;
    settings->debug.display = true;

    const std::string mainUrl = "https://www.av-test.org/en/antivirus/home-windows/windows-10/";

    std::vector<std::string> urls;
    urls.emplace_back(mainUrl + "august-2020");
//    urls.emplace_back(mainUrl + "june-2020");

    std::vector<core::structure::antivirus> &toCatalog = core::structure::catalog;
    toCatalog.reserve(32);

    for (std::string &url : urls) {
        core::windows::pc::main::setInformationFrom(url + "/", toCatalog);
    }

    return 0;
}
