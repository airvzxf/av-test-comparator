#include <iostream>
#include "main.h"
#include "../../structure/settings.h"
#include "../../../library/library.h"
#include "helper/values.h"
#include "helper/display.h"
#include "helper/assign.h"

namespace core::windows::pc::main {
    int setInformationFrom(const std::string &url, std::vector<core::structure::antivirus> &toCatalog) {
        if (core::structure::settings::getInstance()->debug.display)
            std::cout << "url: " << url << std::endl;

        std::string htmlCode = library::html::request::getDataFrom(url);
        std::string table = library::html::find::tag::getTableFrom(htmlCode);
        std::string tbody = library::html::find::tag::getTbodyFrom(table);
        std::string tr;
        std::string td;
        int tdCounter;
        unsigned short year = 0;
        unsigned short month = 0;
        std::string company;
        std::string version;
        unsigned short topProduct = 0;
        float protection = 0;
        float performance = 0;
        float usability = 0;
        std::string link;
        int exists;

        do {
            tr = library::html::extract::tag::getTrFrom(tbody);
            tdCounter = 0;
            exists = false;

            do {
                td = library::html::extract::tag::getTdFrom(tr);
                if (tdCounter == 0) {
                    company = getCompanyFrom(td);
                    version = getProductFrom(td);
                } else if (tdCounter == 1) {
                    topProduct = getCertifiedFrom(td);
                } else if (tdCounter == 2) {
                    protection = getProtectionFrom(td);
                } else if (tdCounter == 3) {
                    performance = getPerformanceFrom(td);
                } else if (tdCounter == 4) {
                    usability = getUsabilityFrom(td);
                    link = getLinkFrom(td);
                    month = getMonthFrom(link);
                    year = getYearFrom(link);
                }
                tdCounter++;
            } while (!td.empty());

            if (company.empty())
                continue;

            if (core::structure::settings::getInstance()->debug.display) {
                std::cout << "company:     -" << company << "-" << std::endl;
                std::cout << "version:     -" << version << "-" << std::endl;
                std::cout << "topProduct:  -" << topProduct << "-" << std::endl;
                std::cout << "protection:  -" << protection << "-" << std::endl;
                std::cout << "performance: -" << performance << "-" << std::endl;
                std::cout << "usability:   -" << usability << "-" << std::endl;
                std::cout << "year:        -" << year << "-" << std::endl;
                std::cout << "month:       -" << month << "-" << std::endl;
                std::cout << "link:        -" << link << std::endl;
            }

            unsigned long index = 0;
            for (const auto &antivirus: toCatalog) {
                if (antivirus.company == company) {
                    exists = true;
                    break;
                }
                index++;
            }

            if (!exists) {
                toCatalog.emplace_back(core::structure::antivirus(company));
                index = toCatalog.size() - 1;
            }

            if (!toCatalog.empty()) {
                toCatalog.at(index).general.reviews += 1;
                toCatalog.at(index).general.topProduct += topProduct;
                toCatalog.at(index).general.protection += protection;
                toCatalog.at(index).general.performance += performance;
                toCatalog.at(index).general.usability += usability;
                toCatalog.at(index).results.emplace_back();
                if (!toCatalog.at(index).results.empty()) {
                    toCatalog.at(index).results.back().year = year;
                    toCatalog.at(index).results.back().month = month;
                    toCatalog.at(index).results.back().version = version;
                    toCatalog.at(index).results.back().topProduct = topProduct;
                    toCatalog.at(index).results.back().protection = protection;
                    toCatalog.at(index).results.back().performance = performance;
                    toCatalog.at(index).results.back().usability = usability;
                }
                assignDetailFrom(toCatalog, index, link);
            }

            if (core::structure::settings::getInstance()->debug.display)
                std::cout << std::endl;
        } while (!tr.empty());

        if (core::structure::settings::getInstance()->debug.display)
            displayFrom(toCatalog);

        return 0;
    }
}
