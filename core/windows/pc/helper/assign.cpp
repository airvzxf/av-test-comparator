#include "assign.h"
#include "../detail.h"

void
assignDetailFrom(std::vector<core::structure::antivirus> &catalog, unsigned long withIndex, std::string &withLink) {
    core::windows::pc::detail::setInformationFrom(withLink, catalog[withIndex].results.back());
    core::structure::antivirus::result &result = catalog[withIndex].results.back();
    catalog[withIndex].general.dayZeroPrev += result.dayZeroPrev;
    catalog[withIndex].general.dayZeroNow += result.dayZeroNow;
    catalog[withIndex].general.detectionPrev += result.detectionPrev;
    catalog[withIndex].general.detectionNow += result.detectionNow;
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
    catalog[withIndex].general.falseWarningsPrev += result.falseWarningsPrev;
    catalog[withIndex].general.falseWarningsNow += result.falseWarningsNow;
    catalog[withIndex].general.falseDetectionsPrev += result.falseDetectionsPrev;
    catalog[withIndex].general.falseDetectionsNow += result.falseDetectionsNow;
    catalog[withIndex].general.falseWarnings += result.falseWarnings;
    catalog[withIndex].general.falseBlockages += result.falseBlockages;
}