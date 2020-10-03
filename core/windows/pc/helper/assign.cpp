#include "assign.h"
#include "../detail.h"

void
assignDetailFrom(std::vector<core::structure::antivirus> &catalog, unsigned long withIndex, std::string &withLink) {
    core::windows::pc::detail::setInformationFrom(withLink, catalog.at(withIndex).results.back());
    core::structure::antivirus::result &result = catalog.at(withIndex).results.back();
    catalog.at(withIndex).general.dayZeroPrev += result.dayZeroPrev;
    catalog.at(withIndex).general.dayZeroNow += result.dayZeroNow;
    catalog.at(withIndex).general.detectionPrev += result.detectionPrev;
    catalog.at(withIndex).general.detectionNow += result.detectionNow;
    catalog.at(withIndex).general.slowingDownStand += result.slowingDownStand;
    catalog.at(withIndex).general.slowingDownHigh += result.slowingDownHigh;
    catalog.at(withIndex).general.slowerDownStand += result.slowerDownStand;
    catalog.at(withIndex).general.slowerDownHigh += result.slowerDownHigh;
    catalog.at(withIndex).general.slowerLaunchStand += result.slowerLaunchStand;
    catalog.at(withIndex).general.slowerLaunchHigh += result.slowerLaunchHigh;
    catalog.at(withIndex).general.slowerInstallationStand += result.slowerInstallationStand;
    catalog.at(withIndex).general.slowerInstallationHigh += result.slowerInstallationHigh;
    catalog.at(withIndex).general.slowerCopyingStand += result.slowerCopyingStand;
    catalog.at(withIndex).general.slowerCopyingHigh += result.slowerCopyingHigh;
    catalog.at(withIndex).general.falseWarningsPrev += result.falseWarningsPrev;
    catalog.at(withIndex).general.falseWarningsNow += result.falseWarningsNow;
    catalog.at(withIndex).general.falseDetectionsPrev += result.falseDetectionsPrev;
    catalog.at(withIndex).general.falseDetectionsNow += result.falseDetectionsNow;
    catalog.at(withIndex).general.falseWarnings += result.falseWarnings;
    catalog.at(withIndex).general.falseBlockages += result.falseBlockages;
}