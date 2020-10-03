#include <iostream>
#include "values.h"
#include "../../../../library/library.h"
#include "../../../structure/settings.h"

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
