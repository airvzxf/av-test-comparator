#include <iostream>
#include "main.h"
#include "detail.h"
#include "../../structure/settings.h"
#include "../../../library/library.h"

std::string getCompanyFrom(std::string &htmlCode);

std::string getProductFrom(std::string &htmlCode);

unsigned short getCertifiedFrom(std::string &htmlCode);

float getProtectionFrom(std::string &htmlCode);

float getPerformanceFrom(std::string &htmlCode);

float getUsabilityFrom(std::string &htmlCode);

std::string getLinkFrom(std::string &htmlCode);

unsigned short getYearFrom(std::string &link);

unsigned short getMonthFrom(std::string &link);

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
                core::windows::pc::detail::setInformationFrom(link, toCatalog.at(index).results.back());
                structure::antivirus::result &result = toCatalog.at(index).results.back();
                toCatalog.at(index).general.dayZeroPrev += result.dayZeroPrev;
                toCatalog.at(index).general.dayZeroNow += result.dayZeroNow;
                toCatalog.at(index).general.detectionPrev += result.detectionPrev;
                toCatalog.at(index).general.detectionNow += result.detectionNow;
                toCatalog.at(index).general.slowingDownStand += result.slowingDownStand;
                toCatalog.at(index).general.slowingDownHigh += result.slowingDownHigh;
                toCatalog.at(index).general.slowerDownStand += result.slowerDownStand;
                toCatalog.at(index).general.slowerDownHigh += result.slowerDownHigh;
                toCatalog.at(index).general.slowerLaunchStand += result.slowerLaunchStand;
                toCatalog.at(index).general.slowerLaunchHigh += result.slowerLaunchHigh;
                toCatalog.at(index).general.slowerInstallationStand += result.slowerInstallationStand;
                toCatalog.at(index).general.slowerInstallationHigh += result.slowerInstallationHigh;
                toCatalog.at(index).general.slowerCopyingStand += result.slowerCopyingStand;
                toCatalog.at(index).general.slowerCopyingHigh += result.slowerCopyingHigh;
                toCatalog.at(index).general.falseWarningsPrev += result.falseWarningsPrev;
                toCatalog.at(index).general.falseWarningsNow += result.falseWarningsNow;
                toCatalog.at(index).general.falseDetectionsPrev += result.falseDetectionsPrev;
                toCatalog.at(index).general.falseDetectionsNow += result.falseDetectionsNow;
                toCatalog.at(index).general.falseWarnings += result.falseWarnings;
                toCatalog.at(index).general.falseBlockages += result.falseBlockages;
            }

            if (core::structure::settings::getInstance()->debug.display)
                std::cout << std::endl;
        } while (!tr.empty());

        if (core::structure::settings::getInstance()->debug.display) {
            for (const auto &current : toCatalog) {
                std::cout << "company: " << current.company << std::endl;
                std::cout << "general.reviews:     " << current.general.reviews << std::endl;
                std::cout << "general.topProduct:  " << current.general.topProduct << std::endl;
                std::cout << "general.protection:  " << current.general.protection << std::endl;
                std::cout << "general.performance: " << current.general.performance << std::endl;
                std::cout << "general.usability:   " << current.general.usability << std::endl;
                std::cout << "general.dayZeroPrev:             " << current.general.dayZeroPrev << std::endl;
                std::cout << "general.dayZeroNow:              " << current.general.dayZeroNow << std::endl;
                std::cout << "general.detectionPrev:           " << current.general.detectionPrev << std::endl;
                std::cout << "general.detectionNow:            " << current.general.detectionNow << std::endl;
                std::cout << "general.slowingDownStand:        " << current.general.slowingDownStand << std::endl;
                std::cout << "general.slowingDownHigh:         " << current.general.slowingDownHigh << std::endl;
                std::cout << "general.slowerDownStand:         " << current.general.slowerDownStand << std::endl;
                std::cout << "general.slowerDownHigh:          " << current.general.slowerDownHigh << std::endl;
                std::cout << "general.slowerLaunchStand:       " << current.general.slowerLaunchStand << std::endl;
                std::cout << "general.slowerLaunchHigh:        " << current.general.slowerLaunchHigh << std::endl;
                std::cout << "general.slowerInstallationStand: " << current.general.slowerInstallationStand
                          << std::endl;
                std::cout << "general.slowerInstallationHigh:  " << current.general.slowerInstallationHigh << std::endl;
                std::cout << "general.slowerCopyingStand:      " << current.general.slowerCopyingStand << std::endl;
                std::cout << "general.slowerCopyingHigh:       " << current.general.slowerCopyingHigh << std::endl;
                std::cout << "general.falseWarningsPrev:       " << current.general.falseWarningsPrev << std::endl;
                std::cout << "general.falseWarningsNow:        " << current.general.falseWarningsNow << std::endl;
                std::cout << "general.falseDetectionsPrev:     " << current.general.falseDetectionsPrev << std::endl;
                std::cout << "general.falseDetectionsNow:      " << current.general.falseDetectionsNow << std::endl;
                std::cout << "general.falseWarnings:           " << current.general.falseWarnings << std::endl;
                std::cout << "general.falseBlockages:          " << current.general.falseBlockages << std::endl;
                std::cout << "------------------------------------------------------------" << std::endl;
                for (const auto &result : current.results) {
                    std::cout << "result.year:        " << result.year << std::endl;
                    std::cout << "result.month:       " << result.month << std::endl;
                    std::cout << "result.version:     " << result.version << std::endl;
                    std::cout << "result.topProduct:  " << result.topProduct << std::endl;
                    std::cout << "result.protection:  " << result.protection << std::endl;
                    std::cout << "result.performance: " << result.performance << std::endl;
                    std::cout << "result.usability:   " << result.usability << std::endl;
                    std::cout << "---------------" << std::endl;
                    std::cout << "result.dayZeroPrev:             " << result.dayZeroPrev << std::endl;
                    std::cout << "result.dayZeroNow:              " << result.dayZeroNow << std::endl;
                    std::cout << "result.detectionPrev:           " << result.detectionPrev << std::endl;
                    std::cout << "result.detectionNow:            " << result.detectionNow << std::endl;
                    std::cout << "result.slowingDownStand:        " << result.slowingDownStand << std::endl;
                    std::cout << "result.slowingDownHigh:         " << result.slowingDownHigh << std::endl;
                    std::cout << "result.slowerDownStand:         " << result.slowerDownStand << std::endl;
                    std::cout << "result.slowerDownHigh:          " << result.slowerDownHigh << std::endl;
                    std::cout << "result.slowerLaunchStand:       " << result.slowerLaunchStand << std::endl;
                    std::cout << "result.slowerLaunchHigh:        " << result.slowerLaunchHigh << std::endl;
                    std::cout << "result.slowerInstallationStand: " << result.slowerInstallationStand << std::endl;
                    std::cout << "result.slowerInstallationHigh:  " << result.slowerInstallationHigh << std::endl;
                    std::cout << "result.slowerCopyingStand:      " << result.slowerCopyingStand << std::endl;
                    std::cout << "result.slowerCopyingHigh:       " << result.slowerCopyingHigh << std::endl;
                    std::cout << "result.falseWarningsPrev:       " << result.falseWarningsPrev << std::endl;
                    std::cout << "result.falseWarningsNow:        " << result.falseWarningsNow << std::endl;
                    std::cout << "result.falseDetectionsPrev:     " << result.falseDetectionsPrev << std::endl;
                    std::cout << "result.falseDetectionsNow:      " << result.falseDetectionsNow << std::endl;
                    std::cout << "result.falseWarnings:           " << result.falseWarnings << std::endl;
                    std::cout << "result.falseBlockages:          " << result.falseBlockages << std::endl;
                    std::cout << "------------------------------" << std::endl;
                }
                std::cout << std::endl;
            }
        }

        return 0;
    }
}

std::string getCompanyFrom(std::string &htmlCode) {
    std::string text = library::html::find::tag::getStrongFrom(htmlCode);
    return library::utility::text::clean(text);
}

std::string getProductFrom(std::string &htmlCode) {
    std::string text = library::html::find::inner::getTextFrom(htmlCode, "style=\"max-width:220px\">", "</span>");
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
        if (core::structure::settings::getInstance()->error.display)
            std::cerr << "Error: Trying to get the PROTECTION value from the general page." << std::endl;
        return 0;
    }
}

float getPerformanceFrom(std::string &htmlCode) {
    std::string text = library::html::find::tag::getDataLabelFrom(htmlCode);
    try {
        return std::stof(text);
    }
    catch (const std::exception &error) {
        if (core::structure::settings::getInstance()->error.display)
            std::cerr << "Error: Trying to get the PERFORMANCE value from the general page." << std::endl;
        return 0;
    }
}

float getUsabilityFrom(std::string &htmlCode) {
    std::string text = library::html::find::tag::getDataLabelFrom(htmlCode);
    try {
        return std::stof(text);
    }
    catch (const std::exception &error) {
        if (core::structure::settings::getInstance()->error.display)
            std::cerr << "Error: Trying to get the USABILITY value from the general page." << std::endl;
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
