#include <iostream>
#include <utility>
#include <vector>
#include <curl/curl.h>
#include "library/library.h"

static std::string errorMessage;
static const char *userAgent = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0";

struct antivirus {
    std::string name;

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
        std::string version;
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

    std::vector<result> results;
};

std::vector<antivirus> allAntivirus;

static size_t writeCallbackWith(void *contents, size_t size, size_t memoryBytes, void *userData);

static int extractInformationFrom(const std::string &url);

static std::string getHtmlTableFrom(std::string &htmlCode);

static std::string getHtmlTbodyFrom(std::string &htmlCode);

static std::string getHtmlTrFrom(std::string &htmlCode);

static std::string getHtmlTdFrom(std::string &htmlCode);

static std::string getProducerFrom(std::string &htmlCode);

static std::string getProducerVersionFrom(std::string &htmlCode);

static unsigned short getCertifiedFrom(std::string &htmlCode);

static float getProtectionFrom(std::string &htmlCode);

static float getPerformanceFrom(std::string &htmlCode);

static float getUsabilityFrom(std::string &htmlCode);

static std::string getLinkFrom(std::string &htmlCode);

static unsigned short getYearFrom(std::string &link);

static unsigned short getMonthFrom(std::string &link);

static size_t writeCallbackWith(void *contents, size_t size, size_t memoryBytes, void *userData) {
    ((std::string *) userData)->append((char *) contents, size * memoryBytes);
    return size * memoryBytes;
}

static std::string getHtmlCodeFrom(const std::string &url) {
    CURL *curl;
    CURLcode res = CURL_LAST;
    std::string readBuffer;

    curl = curl_easy_init();
    if (!curl) {
        errorMessage = "CURL Error: ";
        errorMessage += curl_easy_strerror(res);
        throw std::runtime_error(errorMessage.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallbackWith);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        errorMessage = "CURL Error: ";
        errorMessage += curl_easy_strerror(res);
        throw std::runtime_error(errorMessage.c_str());
    }

    curl_easy_cleanup(curl);

    return readBuffer;
}

static int extractInformationFrom(const std::string &url) {
    std::string htmlCode = getHtmlCodeFrom(url);
    std::string table = getHtmlTableFrom(htmlCode);
    std::string tbody = getHtmlTbodyFrom(table);
    std::string tr;
    std::string td;
    int tdCounter;
    unsigned short year = 0;
    unsigned short month = 0;
    std::string producer;
    std::string version;
    unsigned short topProduct = 0;
    float protection = 0;
    float performance = 0;
    float usability = 0;
    std::string link;
    int exists;
    do {
        tr = getHtmlTrFrom(tbody);
        tdCounter = 0;
        exists = false;
        do {
            td = getHtmlTdFrom(tr);
            if (tdCounter == 0) {
                producer = getProducerFrom(td);
                version = getProducerVersionFrom(td);
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

        if (producer.empty())
            continue;

        std::cout << "producer:    -" << producer << "-" << std::endl;
        std::cout << "version:     -" << version << "-" << std::endl;
        std::cout << "topProduct:  -" << topProduct << "-" << std::endl;
        std::cout << "protection:  -" << protection << "-" << std::endl;
        std::cout << "performance: -" << performance << "-" << std::endl;
        std::cout << "usability:   -" << usability << "-" << std::endl;
        std::cout << "link:        -" << link << "-" << std::endl;
        std::cout << "year:        -" << year << "-" << std::endl;
        std::cout << "month:       -" << month << "-" << std::endl;

        unsigned long index = 0;
        for (const auto &a: allAntivirus) {
            if (a.name == producer) {
                exists = true;
                break;
            }
            index++;
        }

        if (!exists) {
            allAntivirus.emplace_back(antivirus(producer));
            index = allAntivirus.size() - 1;
            std::cout << "Not exists!" << std::endl;
        }
        std::cout << "index: " << index << std::endl;

        if (!allAntivirus.empty()) {
            allAntivirus.at(index).general.reviews += 1;
            allAntivirus.at(index).general.topProduct += topProduct;
            allAntivirus.at(index).general.protection += protection;
            allAntivirus.at(index).general.performance += performance;
            allAntivirus.at(index).general.usability += usability;
            allAntivirus.at(index).results.emplace_back();
            if (!allAntivirus.at(index).results.empty()) {
                allAntivirus.at(index).results.back().year = year;
                allAntivirus.at(index).results.back().month = month;
                allAntivirus.at(index).results.back().version = version;
                allAntivirus.at(index).results.back().topProduct = topProduct;
                allAntivirus.at(index).results.back().protection = protection;
                allAntivirus.at(index).results.back().performance = performance;
                allAntivirus.at(index).results.back().usability = usability;
            }
        }
        std::cout << std::endl;
    } while (!tr.empty());

    for (const auto &current : allAntivirus) {
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

static std::string getHtmlTableFrom(std::string &htmlCode) {
    return library::html::extract::outer::getTextFrom(htmlCode, "<table>", "</table>");
}

static std::string getHtmlTbodyFrom(std::string &htmlCode) {
    return library::html::extract::outer::getTextFrom(htmlCode, "<tbody>", "</tbody>");
}

static std::string getHtmlTrFrom(std::string &htmlCode) {
    return library::html::extract::outer::getTextFrom(htmlCode, "<tr", "</tr>", true, false);
}

static std::string getHtmlTdFrom(std::string &htmlCode) {
    return library::html::extract::outer::getTextFrom(htmlCode, "<td", "</td>", true, false);
}

static std::string getProducerFrom(std::string &htmlCode) {
    std::string text = library::html::extract::inner::getTextFrom(htmlCode, "<strong>", "</strong>");
    return library::utility::text::clean(text);
}

static std::string getProducerVersionFrom(std::string &htmlCode) {
    std::string text = library::html::extract::inner::getTextFrom(htmlCode, "style=\"max-width:220px\">", "</span>");
    return library::utility::text::clean(text);
}

static unsigned short getCertifiedFrom(std::string &htmlCode) {
    std::string url = library::html::extract::inner::getTextFrom(htmlCode, "src=\"", "\" alt=\"");
    std::size_t position = url.find("_tp_");
    if (position != std::string::npos)
        return 1;
    return 0;
}

static float getProtectionFrom(std::string &htmlCode) {
    std::string text = library::html::extract::inner::getTextFrom(htmlCode, "data-label=\"", "\">");
    try {
        return std::stof(text);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the PROTECTION value from the general page." << std::endl << std::endl;
        return 0;
    }
}

static float getPerformanceFrom(std::string &htmlCode) {
    std::string text = library::html::extract::inner::getTextFrom(htmlCode, "data-label=\"", "\">");
    try {
        return std::stof(text);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the PERFORMANCE value from the general page." << std::endl << std::endl;
        return 0;
    }
}

static float getUsabilityFrom(std::string &htmlCode) {
    std::string text = library::html::extract::inner::getTextFrom(htmlCode, "data-label=\"", "\">");
    try {
        return std::stof(text);
    }
    catch (const std::exception &error) {
        std::cerr << "Error: Trying to get the USABILITY value from the general page." << std::endl << std::endl;
        return 0;
    }
}

static std::string getLinkFrom(std::string &htmlCode) {
    std::string text = library::html::extract::inner::getTextFrom(htmlCode, "href=\"", "\" tabindex=");
    return "https://www.av-test.org" + library::utility::text::clean(text) + "/";
}

static unsigned short getYearFrom(std::string &link) {
    std::string month = library::html::extract::inner::getTextFrom(link, "windows-10/", "-");
    transform(month.begin(), month.end(), month.begin(), ::tolower);
    std::string text = library::html::extract::inner::getTextFrom(link, "windows-10/" + month + "-", "/");
    return (unsigned short) std::strtoul(text.c_str(), nullptr, 0);
}

static unsigned short getMonthFrom(std::string &link) {
    std::string text = library::html::extract::inner::getTextFrom(link, "windows-10/", "-");
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

int main() {
    const std::string mainUrl = "https://www.av-test.org/en/antivirus/home-windows/windows-10/";

    allAntivirus.reserve(30);

    std::vector<std::string> urls;
    urls.emplace_back(mainUrl + "august-2020/");
//    urls.emplace_back(mainUrl + "june-2020/");

    for (std::string &url : urls) {
        std::cout << "url: " << url << std::endl << std::endl;
        extractInformationFrom(url);
    }

    std::cout << "sizeof:   " << sizeof(allAntivirus) << '\n';
    std::cout << "size:     " << allAntivirus.size() << '\n';
    std::cout << "capacity: " << allAntivirus.capacity() << '\n';

    return 0;
}
