#include <iostream>
#include <utility>
#include <vector>
#include <curl/curl.h>

static std::string errorMessage;
static const char *userAgent = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0";

struct antivirus {
    std::string name;

    explicit antivirus(std::string name) {
        this->name = std::move(name);
    }

    struct general {
        unsigned short topProduct;
        float protection;
        float performance;
        float usability;
    } general{};

    explicit antivirus() {
        this->general.topProduct = 0;
        this->general.protection = 0;
        this->general.performance = 0;
        this->general.usability = 0;
    }

    struct result {
        unsigned short year;
        unsigned short month;
        std::string version;
        unsigned short topProduct;
        float protection;
        float dayZeroPrev;
        float dayZeroNow;
        float detectionPrev;
        float detectionNow;
        float performance;
        float slowingDownStand;
        float slowingDownHigh;
        float slowerDownStand;
        float slowerDownHigh;
        float slowerLaunchStand;
        float slowerLaunchHigh;
        float slowerInstallationStand;
        float slowerInstallationHigh;
        float slowerCopyingStand;
        float slowerCopyingHigh;
        float usability;
        float falseWarningsPrev;
        float falseWarningsNow;
        float falseDetectionsPrev;
        float falseDetectionsNow;
        float falseWarnings;
        float falseBlockages;
    };

    std::vector<result> results;
};

std::vector<antivirus> allAntivirus;

static size_t writeCallbackWith(void *contents, size_t size, size_t memoryBytes, void *userData);

static int extractInformationFrom(const std::string &url);

static std::string
getHtmlTagFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag, bool extract,
               bool displayError);

static std::string cleanText(std::string text);

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

std::string &ltrim(std::string &str, const std::string &chars = "\t\n\v\f\r ") {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string &rtrim(std::string &str, const std::string &chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string &trim(std::string &str, const std::string &chars = "\t\n\v\f\r ") {
    return ltrim(rtrim(str, chars), chars);
}

void replaceAll(std::string &str, const std::string &old, const std::string &repl) {
    size_t pos = 0;
    while ((pos = str.find(old, pos)) != std::string::npos) {
        str.replace(pos, old.length(), repl);
        pos += repl.length();
    }
}

std::string convertEscapeCharacters(std::string &text) {
    replaceAll(text, std::string("&amp;"), std::string("&"));
    replaceAll(text, std::string("&apos;"), std::string("'"));
    replaceAll(text, std::string("&quot;"), std::string("\""));
    replaceAll(text, std::string("&gt;"), std::string(">"));
    replaceAll(text, std::string("&lt;"), std::string("<"));
    return text;
}

static size_t writeCallbackWith(void *contents, size_t size, size_t memoryBytes, void *userData) {
    ((std::string *) userData)->append((char *) contents, size * memoryBytes);
    return size * memoryBytes;
}

static int extractInformationFrom(const std::string &url) {
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

    std::string table = getHtmlTableFrom(readBuffer);
    std::string tbody = getHtmlTbodyFrom(table);
    std::string tr;
    std::string td;
    unsigned short year;
    unsigned short month;
    std::string producer;
    std::string version;
    unsigned short topProduct;
    float protection;
    float performance;
    float usability;
    std::string link;
    int tdCounter;
    do {
        tr = getHtmlTrFrom(tbody);
        tdCounter = 0;
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
        if (!producer.empty()) {
            std::cout << "producer:    -" << producer << "-" << std::endl;
            std::cout << "version:     -" << version << "-" << std::endl;
            std::cout << "topProduct:  -" << topProduct << "-" << std::endl;
            std::cout << "protection:  -" << protection << "-" << std::endl;
            std::cout << "performance: -" << performance << "-" << std::endl;
            std::cout << "usability:   -" << usability << "-" << std::endl;
            std::cout << "link:        -" << link << "-" << std::endl;
            std::cout << "year:        -" << year << "-" << std::endl;
            std::cout << "month:       -" << month << "-" << std::endl;
            allAntivirus.emplace_back(antivirus(producer));
            if (!allAntivirus.empty()) {
                allAntivirus.back().general.topProduct += topProduct;
                allAntivirus.back().general.protection += protection;
                allAntivirus.back().general.performance += performance;
                allAntivirus.back().general.usability += usability;
                allAntivirus.back().results.emplace_back();
                if (!allAntivirus.back().results.empty()) {
                    allAntivirus.back().results.back().year = year;
                    allAntivirus.back().results.back().month = month;
                    allAntivirus.back().results.back().version = version;
                    allAntivirus.back().results.back().topProduct = topProduct;
                    allAntivirus.back().results.back().protection = protection;
                    allAntivirus.back().results.back().performance = performance;
                    allAntivirus.back().results.back().usability = usability;
                }
            }
            std::cout << std::endl;
        }
    } while (!tr.empty());

    for (const auto &current : allAntivirus) {
        std::cout << "name: " << current.name << std::endl;
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

static std::string
getHtmlTagFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag, bool extract = false,
               bool displayError = true) {
    std::string tagContent;

    if (htmlCode.empty())
        return tagContent;

    std::size_t firstPosition = htmlCode.find(firstTag);
    if (firstPosition == std::string::npos) {
        if (displayError)
            std::cerr << "Error: Not found the first HTML tag -> " << firstTag << "." << std::endl;
        return tagContent;
    }

    std::size_t lastPosition = htmlCode.find(lastTag, firstPosition + firstTag.size());
    if (lastPosition == std::string::npos) {
        if (displayError)
            std::cerr << "Error: Not found the last HTML tag -> " << lastTag << "." << std::endl;
        return tagContent;
    }

    std::size_t size = lastPosition - firstPosition + lastTag.size();
    tagContent = htmlCode.substr(firstPosition, size);

    if (extract) {
        const std::string firstCode = htmlCode.substr(0, firstPosition);
        const std::string lastCode = htmlCode.substr(lastPosition + lastTag.size());
        htmlCode = firstCode + lastCode;
    }

    return tagContent;
}

static std::string getHtmlInnerFrom(std::string &htmlCode, const std::string &firstTag, const std::string &lastTag) {
    std::string tagContent;

    if (htmlCode.empty())
        return tagContent;

    std::size_t firstPosition = htmlCode.find(firstTag);
    if (firstPosition == std::string::npos)
        return tagContent;

    std::size_t innerPosition = firstPosition + firstTag.size();
    std::size_t lastPosition = htmlCode.find(lastTag, innerPosition);
    if (lastPosition == std::string::npos)
        return tagContent;

    std::size_t size = lastPosition - innerPosition;
    tagContent = htmlCode.substr(innerPosition, size);

    return tagContent;
}

static std::string cleanText(std::string text) {
    std::string trimText = trim(text);
    return convertEscapeCharacters(trimText);
}

static std::string getHtmlTableFrom(std::string &htmlCode) {
    return getHtmlTagFrom(htmlCode, "<table>", "</table>");
}

static std::string getHtmlTbodyFrom(std::string &htmlCode) {
    return getHtmlTagFrom(htmlCode, "<tbody>", "</tbody>");
}

static std::string getHtmlTrFrom(std::string &htmlCode) {
    return getHtmlTagFrom(htmlCode, "<tr", "</tr>", true, false);
}

static std::string getHtmlTdFrom(std::string &htmlCode) {
    return getHtmlTagFrom(htmlCode, "<td", "</td>", true, false);
}

static std::string getProducerFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "<strong>", "</strong>");
    return cleanText(text);
}

static std::string getProducerVersionFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "style=\"max-width:220px\">", "</span>");
    return cleanText(text);
}

static unsigned short getCertifiedFrom(std::string &htmlCode) {
    std::string url = getHtmlInnerFrom(htmlCode, "src=\"", "\" alt=\"");
    std::size_t position = url.find("_tp_");
    if (position != std::string::npos)
        return 1;
    return 0;
}

static float getProtectionFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "data-label=\"", "\">");
    return std::stof(text);
}

static float getPerformanceFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "data-label=\"", "\">");
    return std::stof(text);
}

static float getUsabilityFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "data-label=\"", "\">");
    return std::stof(text);
}

static std::string getLinkFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "href=\"", "\" tabindex=");
    return "https://www.av-test.org" + cleanText(text) + "/";
}

static unsigned short getYearFrom(std::string &link) {
    std::string month = getHtmlInnerFrom(link, "windows-10/", "-");
    transform(month.begin(), month.end(), month.begin(), ::tolower);
    std::string text = getHtmlInnerFrom(link, "windows-10/" + month + "-", "/");
    return std::strtoul(text.c_str(), nullptr, 0);
}

static unsigned short getMonthFrom(std::string &link) {
    std::string text = getHtmlInnerFrom(link, "windows-10/", "-");
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    if (text == "january")
        return 1;
    if (text == "february")
        return 2;
    if (text == "March")
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

    std::vector<std::string> urls;
    urls.emplace_back(mainUrl + "august-2020/");
    urls.emplace_back(mainUrl + "june-2020/");

    for (std::string &url : urls) {
        std::cout << "url: " << url << std::endl << std::endl;
        extractInformationFrom(url);
    }

    return 0;
}