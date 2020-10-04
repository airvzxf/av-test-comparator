#include "assign.h"
#include "../detail.h"

void
assignDetailFrom(std::vector<core::structure::antivirus> &catalog, unsigned long withIndex, std::string &withLink) {
    core::windows::pc::detail::setInformationFrom(withLink, catalog[withIndex].results.back());
    core::structure::antivirus::result &result = catalog[withIndex].results.back();
    catalog[withIndex].general.dayZero += result.dayZeroPrev;
    catalog[withIndex].general.dayZero += result.dayZeroNow;
    catalog[withIndex].general.detection += result.detectionPrev;
    catalog[withIndex].general.detection += result.detectionNow;
    catalog[withIndex].general.protectionOverall +=
            catalog[withIndex].general.dayZero + catalog[withIndex].general.detection;
    catalog[withIndex].general.slowingDownStand += result.slowingDownStand;
    catalog[withIndex].general.slowingDownHigh += result.slowingDownHigh;
    catalog[withIndex].general.slowerDownStand += result.slowerDownStand;
    catalog[withIndex].general.slowerDownHigh += result.slowerDownHigh;
    catalog[withIndex].general.slowerLaunchStand += result.slowerLaunchStand;
    catalog[withIndex].general.slowerLaunchHigh += result.slowerLaunchHigh;
    catalog[withIndex].general.slowerInstallationStand += result.slowerInstallationStand;
    catalog[withIndex].general.slowerInstallationHigh += result.slowerInstallationHigh;
    catalog[withIndex].general.slowerCopyingStand += result.slowerCopyingStand;
    catalog[withIndex].general.slowerCopyingHigh += result.slowerCopyingHigh;
    catalog[withIndex].general.performanceOverall +=
            result.slowingDownStand + result.slowingDownHigh + result.slowerDownStand + result.slowerDownHigh
            + result.slowerLaunchStand + result.slowerLaunchHigh + result.slowerInstallationStand
            + result.slowerInstallationHigh + result.slowerCopyingStand + result.slowerCopyingHigh;
    catalog[withIndex].general.falseWarningsWebsites += result.falseWarningsPrev;
    catalog[withIndex].general.falseWarningsWebsites += result.falseWarningsNow;
    catalog[withIndex].general.falseDetections += result.falseDetectionsPrev;
    catalog[withIndex].general.falseDetections += result.falseDetectionsNow;
    catalog[withIndex].general.falseWarnings += result.falseWarnings;
    catalog[withIndex].general.falseBlockages += result.falseBlockages;
    catalog[withIndex].general.usabilityOverall +=
            result.falseWarningsPrev + result.falseWarningsNow + result.falseDetectionsPrev +
            result.falseDetectionsNow + result.falseWarnings + result.falseBlockages;
}
