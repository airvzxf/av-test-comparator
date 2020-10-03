#include <iostream>
#include "main.h"
#include "../../../library/library.h"

namespace core::windows::pc::main {
    std::string getCompanyFrom(std::string &htmlCode) {
        std::string text = library::html::find::tag::getStrongFrom(htmlCode);
        return library::utility::text::clean(text);
    }

    std::string getProductFrom(std::string &htmlCode) {
        std::string text = library::html::find::inner::getTextFrom(htmlCode, "style=\"max-width:220px\">",
                                                                   "</span>");
        return library::utility::text::clean(text);
    }

    unsigned short getCertifiedFrom(std::string &htmlCode) {
        std::string url = library::html::find::tag::getSrcFrom(htmlCode);
        std::size_t position = url.find("_tp_");
        if (position != std::string::npos)
            return 1;
        return 0;
    }

    float getProtectionFrom(std::string &htmlCode) {
        std::string text = library::html::find::tag::getDataLabelFrom(htmlCode);
        try {
            return std::stof(text);
        }
        catch (const std::exception &error) {
            std::cerr << "Error: Trying to get the PROTECTION value from the general page." << std::endl << std::endl;
            return 0;
        }
    }

    float getPerformanceFrom(std::string &htmlCode) {
        std::string text = library::html::find::tag::getDataLabelFrom(htmlCode);
        try {
            return std::stof(text);
        }
        catch (const std::exception &error) {
            std::cerr << "Error: Trying to get the PERFORMANCE value from the general page." << std::endl << std::endl;
            return 0;
        }
    }

    float getUsabilityFrom(std::string &htmlCode) {
        std::string text = library::html::find::tag::getDataLabelFrom(htmlCode);
        try {
            return std::stof(text);
        }
        catch (const std::exception &error) {
            std::cerr << "Error: Trying to get the USABILITY value from the general page." << std::endl << std::endl;
            return 0;
        }
    }

    std::string getLinkFrom(std::string &htmlCode) {
        std::string text = library::html::find::tag::getHrefFrom(htmlCode);
        return "https://www.av-test.org" + library::utility::text::clean(text) + "/";
    }

    unsigned short getYearFrom(std::string &link) {
        std::string month = library::html::find::inner::getTextFrom(link, "windows-10/", "-");
        transform(month.begin(), month.end(), month.begin(), ::tolower);
        std::string text = library::html::find::inner::getTextFrom(link, "windows-10/" + month + "-", "/");
        return (unsigned short) std::strtoul(text.c_str(), nullptr, 0);
    }

    unsigned short getMonthFrom(std::string &link) {
        std::string text = library::html::find::inner::getTextFrom(link, "windows-10/", "-");
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        if (text == "january")
            return 1;
        if (text == "february")
            return 2;
        if (text == "march")
            return 3;
        if (text == "april")
            return 4;
        if (text == "may")
            return 5;
        if (text == "june")
            return 6;
        if (text == "july")
            return 7;
        if (text == "august")
            return 8;
        if (text == "september")
            return 9;
        if (text == "october")
            return 10;
        if (text == "november")
            return 11;
        return 12;
    }

    int getInformationFrom(const std::string &url, std::vector<core::structure::antivirus> &toCatalog) {
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
            tr = library::html::find::tag::extractTrFrom(tbody);
            tdCounter = 0;
            exists = false;
            do {
                td = library::html::find::tag::extractTdFrom(tr);
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

            std::cout << "company:     -" << company << "-" << std::endl;
            std::cout << "version:     -" << version << "-" << std::endl;
            std::cout << "topProduct:  -" << topProduct << "-" << std::endl;
            std::cout << "protection:  -" << protection << "-" << std::endl;
            std::cout << "performance: -" << performance << "-" << std::endl;
            std::cout << "usability:   -" << usability << "-" << std::endl;
            std::cout << "link:        -" << link << "-" << std::endl;
            std::cout << "year:        -" << year << "-" << std::endl;
            std::cout << "month:       -" << month << "-" << std::endl;

            unsigned long index = 0;
            for (const auto &antivirus: toCatalog) {
                if (antivirus.name == company) {
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
            }
            std::cout << std::endl;
        } while (!tr.empty());

        for (const auto &current : toCatalog) {
            std::cout << "name: " << current.name << std::endl;
            std::cout << "general.reviews:     " << current.general.reviews << std::endl;
            std::cout << "general.topProduct:  " << current.general.topProduct << std::endl;
            std::cout << "general.protection:  " << current.general.protection << std::endl;
            std::cout << "general.performance: " << current.general.performance << std::endl;
            std::cout << "general.usability:   " << current.general.usability << std::endl;
            std::cout << "---------------------------------" << std::endl;
            for (const auto &result : current.results) {
                std::cout << "result.year:        " << result.year << std::endl;
                std::cout << "result.month:       " << result.month << std::endl;
                std::cout << "result.version:     " << result.version << std::endl;
                std::cout << "result.topProduct:  " << result.topProduct << std::endl;
                std::cout << "result.protection:  " << result.protection << std::endl;
                std::cout << "result.performance: " << result.performance << std::endl;
                std::cout << "result.usability:   " << result.usability << std::endl;
                std::cout << "---------------------------------" << std::endl;
            }
            std::cout << std::endl;
        }

        return 0;
    }
}
