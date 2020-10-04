#include <iostream>
#include "display.h"

void displayFrom(std::vector<core::structure::antivirus> &catalog, bool details) {
    for (const auto &current : catalog) {
        std::cout << "company: " << current.company << std::endl;
        std::cout << "general.reviews:     " << current.general.reviews << std::endl;
        std::cout << "general.topProduct:  " << current.general.topProduct << std::endl;
        std::cout << "general.protection:  " << current.general.protection << std::endl;
        std::cout << "general.performance: " << current.general.performance << std::endl;
        std::cout << "general.usability:   " << current.general.usability << std::endl;
        std::cout << "general.dayZero:                 " << current.general.dayZero << std::endl;
        std::cout << "general.detection:               " << current.general.detection << std::endl;
        std::cout << "general.slowingDownStand:        " << current.general.slowingDownStand << std::endl;
        std::cout << "general.slowingDownHigh:         " << current.general.slowingDownHigh << std::endl;
        std::cout << "general.slowerDownStand:         " << current.general.slowerDownStand << std::endl;
        std::cout << "general.slowerDownHigh:          " << current.general.slowerDownHigh << std::endl;
        std::cout << "general.slowerLaunchStand:       " << current.general.slowerLaunchStand << std::endl;
        std::cout << "general.slowerLaunchHigh:        " << current.general.slowerLaunchHigh << std::endl;
        std::cout << "general.slowerInstallationStand: " << current.general.slowerInstallationStand << std::endl;
        std::cout << "general.slowerInstallationHigh:  " << current.general.slowerInstallationHigh << std::endl;
        std::cout << "general.slowerCopyingStand:      " << current.general.slowerCopyingStand << std::endl;
        std::cout << "general.slowerCopyingHigh:       " << current.general.slowerCopyingHigh << std::endl;
        std::cout << "general.falseWarningsWebsites:   " << current.general.falseWarningsWebsites << std::endl;
        std::cout << "general.falseDetections:         " << current.general.falseDetections << std::endl;
        std::cout << "general.falseWarnings:           " << current.general.falseWarnings << std::endl;
        std::cout << "general.falseBlockages:          " << current.general.falseBlockages << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;

        if (!details)
            continue;

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
