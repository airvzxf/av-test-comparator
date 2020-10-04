#include <iostream>
#include <fstream>
#include "export.h"

namespace core::windows::pc::csv {
    void exportFrom(std::vector<core::structure::antivirus> &catalog, const std::string &filename) {
        std::string headerGeneral, headerDetail;
        headerGeneral = "\"Antivirus\nPC\",Reviews,\"Top\nProduct\",\"General\nProtection\n▲\",\"0-day\n▲\","
                        "\"Detection\n▲\",\"General\nPerformance\n▲\",\"Standard PC\nSlowing-down\n▼\","
                        "\"High end PC\nSlowing-down\n▼\",\"Standard PC\nSlower download\n▼\","
                        "\"High end PC\nSlower download\n▼\",\"Standard PC\nSlower launch\n▼\","
                        "\"High end PC\nSlower launch\n▼\",\"Standard PC\nSlower installation\n▼\","
                        "\"High end PC\nSlower installation\n▼\",\"Standard PC\nSlower copying\n▼\","
                        "\"High end PC\nSlower copying\n▼\",\"General\nUsability\n▲\",\"False warnings\nWebsites\n▼\","
                        "\"False detections\n▼\",\"False\nwarnings\n▼\",\"False\nblockages\n▼\",,";
        headerDetail = "Year,Month,Version,\"Top\nProduct\",\"General\nProtection\n▲\",\"July\n0-day\n▲\","
                       "\"August\n0-day\n▲\",\"July\nDetection\n▲\",\"August\nDetection\n▲\","
                       "\"General\nPerformance\n▲\",\"Standard PC\nSlowing-down\n▼\",\"High end PC\nSlowing-down\n▼\","
                       "\"Standard PC\nSlower download\n▼\",\"High end PC\nSlower download\n▼\","
                       "\"Standard PC\nSlower launch\n▼\",\"High end PC\nSlower launch\n▼\","
                       "\"Standard PC\nSlower installation\n▼\",\"High end PC\nSlower installation\n▼\","
                       "\"Standard PC\nSlower copying\n▼\",\"High end PC\nSlower copying\n▼\","
                       "\"General\nUsability\n▲\",\"July\nFalse warnings\n▼\",\"August\nFalse warnings\n▼\","
                       "\"July\nFalse detections\n▼\",\"August\nFalse detections\n▼\",\"False\nwarnings\n▼\","
                       "\"False\nblockages\n▼\",,";

        int maxResults = 0;
        std::string data;
        for (const auto &antivirus : catalog) {
            data += antivirus.company + ",";
            data += std::to_string(antivirus.general.reviews) + ",";
            data += std::to_string(antivirus.general.topProduct) + ",";
            data += std::to_string(antivirus.general.protection) + ",";
            data += std::to_string(antivirus.general.dayZero) + ",";
            data += std::to_string(antivirus.general.detection) + ",";
            data += std::to_string(antivirus.general.performance) + ",";
            data += std::to_string(antivirus.general.slowingDownStand) + ",";
            data += std::to_string(antivirus.general.slowingDownHigh) + ",";
            data += std::to_string(antivirus.general.slowerDownStand) + ",";
            data += std::to_string(antivirus.general.slowerDownHigh) + ",";
            data += std::to_string(antivirus.general.slowerLaunchStand) + ",";
            data += std::to_string(antivirus.general.slowerLaunchHigh) + ",";
            data += std::to_string(antivirus.general.slowerInstallationStand) + ",";
            data += std::to_string(antivirus.general.slowerInstallationHigh) + ",";
            data += std::to_string(antivirus.general.slowerCopyingStand) + ",";
            data += std::to_string(antivirus.general.slowerCopyingHigh) + ",";
            data += std::to_string(antivirus.general.usability) + ",";
            data += std::to_string(antivirus.general.falseWarningsWebsites) + ",";
            data += std::to_string(antivirus.general.falseDetections) + ",";
            data += std::to_string(antivirus.general.falseWarnings) + ",";
            data += std::to_string(antivirus.general.falseBlockages) + ",,";
            int index = 0;
            for (const auto &result : antivirus.results) {
                data += std::to_string(result.year) + ",";
                data += std::to_string(result.month) + ",";
                data += result.version + ",";
                data += std::to_string(result.topProduct) + ",";
                data += std::to_string(result.protection) + ",";
                data += std::to_string(result.dayZeroPrev) + ",";
                data += std::to_string(result.dayZeroNow) + ",";
                data += std::to_string(result.detectionPrev) + ",";
                data += std::to_string(result.detectionNow) + ",";
                data += std::to_string(result.performance) + ",";
                data += std::to_string(result.slowingDownStand) + ",";
                data += std::to_string(result.slowingDownHigh) + ",";
                data += std::to_string(result.slowerDownStand) + ",";
                data += std::to_string(result.slowerDownHigh) + ",";
                data += std::to_string(result.slowerLaunchStand) + ",";
                data += std::to_string(result.slowerLaunchHigh) + ",";
                data += std::to_string(result.slowerInstallationStand) + ",";
                data += std::to_string(result.slowerInstallationHigh) + ",";
                data += std::to_string(result.slowerCopyingStand) + ",";
                data += std::to_string(result.slowerCopyingHigh) + ",";
                data += std::to_string(result.usability) + ",";
                data += std::to_string(result.falseWarningsPrev) + ",";
                data += std::to_string(result.falseWarningsNow) + ",";
                data += std::to_string(result.falseDetectionsPrev) + ",";
                data += std::to_string(result.falseDetectionsNow) + ",";
                data += std::to_string(result.falseWarnings) + ",";
                data += std::to_string(result.falseBlockages) + ",,";
                index++;
                if (index > maxResults)
                    maxResults = index;
            }
            data += "\n";
        }

        std::cout << "maxResults: " << maxResults << std::endl;

        std::ofstream csvFile("./" + filename);
        csvFile << headerGeneral;
        for (int i = 0; i < maxResults; ++i)
            csvFile << headerDetail;
        csvFile << std::endl;
        csvFile << data;
        csvFile.close();
    }
}
