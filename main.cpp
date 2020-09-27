#include <iostream>
#include <vector>
#include <curl/curl.h>

static std::string errorMessage;
static const char *userAgent = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:81.0) Gecko/20100101 Firefox/81.0";

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

static std::string getCertifiedFrom(std::string &htmlCode);

static std::string getProtectionFrom(std::string &htmlCode);

static std::string getPerformanceFrom(std::string &htmlCode);

static std::string getUsabilityFrom(std::string &htmlCode);

static std::string getLinkFrom(std::string &htmlCode);

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
    std::string producer;
    std::string version;
    std::string certified;
    std::string protection;
    std::string performance;
    std::string usability;
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
                certified = getCertifiedFrom(td);
            } else if (tdCounter == 2) {
                protection = getProtectionFrom(td);
            } else if (tdCounter == 3) {
                performance = getPerformanceFrom(td);
            } else if (tdCounter == 4) {
                usability = getUsabilityFrom(td);
                link = getLinkFrom(td);
            }
            tdCounter++;
        } while (!td.empty());
        if (!producer.empty()) {
            std::cout << "producer:    -" << producer << "-" << std::endl;
            std::cout << "version:     -" << version << "-" << std::endl;
            std::cout << "certified:   -" << certified << "-" << std::endl;
            std::cout << "protection:  -" << protection << "-" << std::endl;
            std::cout << "performance: -" << performance << "-" << std::endl;
            std::cout << "usability:   -" << usability << "-" << std::endl;
            std::cout << "link:        -" << link << "-" << std::endl;
            std::cout << std::endl;
        }
    } while (!tr.empty());

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

    std::size_t lastPosition = htmlCode.find(lastTag, firstPosition);
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

    std::size_t lastPosition = htmlCode.find(lastTag, firstPosition);
    if (lastPosition == std::string::npos)
        return tagContent;

    std::size_t innerPosition = firstPosition + firstTag.size();
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

static std::string getCertifiedFrom(std::string &htmlCode) {
    std::string url = getHtmlInnerFrom(htmlCode, "src=\"", "\" alt=\"");
    std::size_t position = url.find("_tp_");
    if (position != std::string::npos)
        return "Top Product";
    return "Certified";
}

static std::string getProtectionFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "data-label=\"", "\">");
    return cleanText(text);
}

static std::string getPerformanceFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "data-label=\"", "\">");
    return cleanText(text);
}

static std::string getUsabilityFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "data-label=\"", "\">");
    return cleanText(text);
}

static std::string getLinkFrom(std::string &htmlCode) {
    std::string text = getHtmlInnerFrom(htmlCode, "href=\"", "\" tabindex=");
    return "https://www.av-test.org" + cleanText(text) + "/";
}

int main() {
    const std::string mainUrl = "https://www.av-test.org/en/antivirus/home-windows/windows-10/";

    std::vector<std::string> urls;
    urls.emplace_back(mainUrl + "august-2020/");
    urls.emplace_back(mainUrl + "june-2020/");

    std::vector<std::string> generalHeaders;
    generalHeaders.emplace_back("Producer");
    generalHeaders.emplace_back("Certified");
    generalHeaders.emplace_back("Protection");
    generalHeaders.emplace_back("Performance");
    generalHeaders.emplace_back("Usability");

    for (std::string &url : urls) {
        std::cout << "url: " << url << std::endl << std::endl;
        extractInformationFrom(url);
    }

    return 0;
}