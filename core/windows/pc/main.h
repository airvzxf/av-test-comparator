#ifndef AV_TEST_COMPARATOR_CORE_WINDOWS_PC_MAIN_H
#define AV_TEST_COMPARATOR_CORE_WINDOWS_PC_MAIN_H

#include <string>
#include <vector>
#include "../../structure/antivirus.h"

namespace core::windows::pc::main {
    int setInformationFrom(std::string &url, std::vector<core::structure::antivirus> &toCatalog);
}
#endif //AV_TEST_COMPARATOR_CORE_WINDOWS_PC_MAIN_H
