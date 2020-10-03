#ifndef AV_TEST_COMPARATOR_CORE_STRUCTURE_ANTIVIRUS_H
#define AV_TEST_COMPARATOR_CORE_STRUCTURE_ANTIVIRUS_H

#include <vector>

namespace core::structure {
    struct antivirus {
        std::string name{};

        explicit antivirus(std::string name) {
            this->name = std::move(name);
        }

        struct general {
            unsigned short reviews{};
            unsigned short topProduct{};
            float protection{};
            float performance{};
            float usability{};
        } general{};

        struct result {
            unsigned short year{};
            unsigned short month{};
            std::string version{};
            unsigned short topProduct{};
            float protection{};
            float dayZeroPrev{};
            float dayZeroNow{};
            float detectionPrev{};
            float detectionNow{};
            float performance{};
            float slowingDownStand{};
            float slowingDownHigh{};
            float slowerDownStand{};
            float slowerDownHigh{};
            float slowerLaunchStand{};
            float slowerLaunchHigh{};
            float slowerInstallationStand{};
            float slowerInstallationHigh{};
            float slowerCopyingStand{};
            float slowerCopyingHigh{};
            float usability{};
            float falseWarningsPrev{};
            float falseWarningsNow{};
            float falseDetectionsPrev{};
            float falseDetectionsNow{};
            float falseWarnings{};
            float falseBlockages{};
        };

        std::vector<result> results{};
    };
}
#endif //AV_TEST_COMPARATOR_CORE_STRUCTURE_ANTIVIRUS_H
