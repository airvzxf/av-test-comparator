#ifndef AV_TEST_COMPARATOR_CORE_WINDOWS_PC_HELPER_VALUES_H
#define AV_TEST_COMPARATOR_CORE_WINDOWS_PC_HELPER_VALUES_H

#include <string>

std::string getCompanyFrom(std::string &htmlCode);

std::string getProductFrom(std::string &htmlCode);

unsigned short getCertifiedFrom(std::string &htmlCode);

float getProtectionFrom(std::string &htmlCode);

float getPerformanceFrom(std::string &htmlCode);

float getUsabilityFrom(std::string &htmlCode);

std::string getLinkFrom(std::string &htmlCode);

unsigned short getYearFrom(std::string &link);

unsigned short getMonthFrom(std::string &link);

#endif //AV_TEST_COMPARATOR_CORE_WINDOWS_PC_HELPER_VALUES_H
