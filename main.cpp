#include <vector>
#include <iostream>
#include "core/core.h"

int main() {
    const std::string mainUrl = "https://www.av-test.org/en/antivirus/home-windows/windows-10/";

    std::vector<std::string> urls;
    urls.emplace_back(mainUrl + "august-2020");
//    urls.emplace_back(mainUrl + "june-2020");

    std::vector<core::structure::antivirus> &catalog = core::structure::catalog;
    catalog.reserve(32);

    for (std::string &url : urls) {
        url += "/";
        std::cout << "url: " << url << std::endl << std::endl;
        core::windows::pc::main::getInformationFrom(url, catalog);
    }

    std::cout << "sizeof:   " << sizeof(catalog) << '\n';
    std::cout << "size:     " << catalog.size() << '\n';
    std::cout << "capacity: " << catalog.capacity() << '\n';

    return 0;
}
