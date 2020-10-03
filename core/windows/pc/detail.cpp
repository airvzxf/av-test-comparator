#include <iostream>
#include "detail.h"
#include "../../../library/library.h"

void getProtectionFrom(std::string &htmlCode, float &prev, float &now);

void getPerformanceFrom(std::string &htmlCode, float &prev, float &now);

void getUsabilityFrom(std::string &htmlCode, float &prev, float &now);

void getUsabilityFrom(std::string &htmlCode, float &value);

namespace core::windows::pc::detail {

    int setInformationFrom(const std::string &url, core::structure::antivirus::result &toResults) {
        std::string htmlCode = library::html::request::getDataFrom(url);

        std::string table;
        std::string tbody;
        std::string tr;
        std::string td;
        std::string dayZeroPrev, dayZeroNow;
        std::string detectionPrev, detectionNow;
        std::string slowingDownStand, slowingDownHigh;
        std::string slowerDownStand, slowerDownHigh;
        std::string slowerLaunchStand, slowerLaunchHigh;
        std::string slowerInstallationStand, slowerInstallationHigh;
        std::string slowerCopyingStand, slowerCopyingHigh;

        // Description table
        table = library::html::extract::tag::getTableFrom(htmlCode);

        // Protection table
        table = library::html::extract::tag::getTableFrom(htmlCode);
        tbody = library::html::find::tag::getTbodyFrom(table);
        getProtectionFrom(tbody, toResults.dayZeroPrev, toResults.dayZeroNow);
        getProtectionFrom(tbody, toResults.detectionPrev, toResults.detectionNow);

        // Performance table
        table = library::html::extract::tag::getTableFrom(htmlCode);
        tbody = library::html::find::tag::getTbodyFrom(table);
        getPerformanceFrom(tbody, toResults.slowingDownStand, toResults.slowingDownHigh);
        getPerformanceFrom(tbody, toResults.slowerDownStand, toResults.slowerDownHigh);
        getPerformanceFrom(tbody, toResults.slowerLaunchStand, toResults.slowerLaunchHigh);
        getPerformanceFrom(tbody, toResults.slowerInstallationStand, toResults.slowerInstallationHigh);
        getPerformanceFrom(tbody, toResults.slowerCopyingStand, toResults.slowerCopyingHigh);

        // Usability table
        table = library::html::extract::tag::getTableFrom(htmlCode);
        tbody = library::html::find::tag::getTbodyFrom(table);
        getUsabilityFrom(tbody, toResults.falseWarningsPrev, toResults.falseWarningsNow);
        getUsabilityFrom(tbody, toResults.falseDetectionsPrev, toResults.falseDetectionsNow);
        getUsabilityFrom(tbody, toResults.falseWarnings);
        getUsabilityFrom(tbody, toResults.falseBlockages);

        return 0;
    }
}

void getProtectionFrom(std::string &htmlCode, float &prev, float &now) {
    std::string tr, td, prevText, nowText;

    tr = library::html::extract::tag::getTrFrom(htmlCode);
    td = library::html::extract::tag::getTdFrom(tr);
    td = library::html::extract::tag::getTdFrom(tr);

    // Last month results
    td = library::html::extract::tag::getTdFrom(tr);
    prevText = library::html::find::inner::getTextFrom(td, "data-type=\"std\">", "%");
    try {
        prev = std::stof(prevText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the PROTECTION PREV value from the details page." << std::endl;
        prev = 0;
    }

    // Actual month results
    td = library::html::extract::tag::getTdFrom(tr);
    nowText = library::html::find::inner::getTextFrom(td, "data-type=\"std\">", "%");
    try {
        now = std::stof(nowText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the PROTECTION NOW value from the details page." << std::endl;
        now = 0;
    }
}

void getPerformanceFrom(std::string &htmlCode, float &prev, float &now) {
    std::string tr, td, prevText, nowText;

    tr = library::html::extract::tag::getTrFrom(htmlCode);
    td = library::html::extract::tag::getTdFrom(tr);
    td = library::html::extract::tag::getTdFrom(tr);

    // Standard results
    td = library::html::extract::tag::getTdFrom(tr);
    prevText = library::html::find::inner::getTextFrom(td, "class=\"fancyGraph\">", "&");
    try {
        prev = std::stof(prevText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the PERFORMANCE PREV value from the details page." << std::endl;
        prev = 0;
    }

    td = library::html::extract::tag::getTdFrom(tr);

    // High End results
    td = library::html::extract::tag::getTdFrom(tr);
    nowText = library::html::find::inner::getTextFrom(td, "class=\"fancyGraph\">", "&");
    try {
        now = std::stof(nowText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the PERFORMANCE NOW value from the details page." << std::endl;
        now = 0;
    }
}

void getUsabilityFrom(std::string &htmlCode, float &prev, float &now) {
    std::string tr, td, prevText, nowText;

    tr = library::html::extract::tag::getTrFrom(htmlCode);
    td = library::html::extract::tag::getTdFrom(tr);
    td = library::html::extract::tag::getTdFrom(tr);

    // Standard results
    td = library::html::extract::tag::getTdFrom(tr);
    prevText = library::html::find::inner::getTextFrom(td, "<td >", "</td>");
    prevText = library::utility::text::trim(prevText);
    try {
        prev = std::stof(prevText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the USABILITY PREV value from the details page." << std::endl;
        prev = 0;
    }


    // High End results
    td = library::html::extract::tag::getTdFrom(tr);
    nowText = library::html::find::inner::getTextFrom(td, "<td >", "</td>");
    nowText = library::utility::text::trim(nowText);
    try {
        now = std::stof(nowText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the USABILITY NOW value from the details page." << std::endl;
        now = 0;
    }
}

void getUsabilityFrom(std::string &htmlCode, float &value) {
    std::string tr, td, valueText;

    tr = library::html::extract::tag::getTrFrom(htmlCode);
    td = library::html::extract::tag::getTdFrom(tr);
    td = library::html::extract::tag::getTdFrom(tr);

    // Standard results
    td = library::html::extract::tag::getTdFrom(tr);
    valueText = library::html::find::inner::getTextFrom(td, "<td  colspan=\"2\">", "</td>");
    valueText = library::utility::text::trim(valueText);
    try {
        value = std::stof(valueText);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the USABILITY VALUE value from the details page." << std::endl;
        value = 0;
    }
}
