#ifndef AV_TEST_COMPARATOR_CORE_WINDOWS_PC_DETAIL_H
#define AV_TEST_COMPARATOR_CORE_WINDOWS_PC_DETAIL_H

#include <string>
#include "../../structure/antivirus.h"

namespace core::windows::pc::detail {
    int setInformationFrom(const std::string &url, core::structure::antivirus::result &toResults);
}
#endif //AV_TEST_COMPARATOR_CORE_WINDOWS_PC_DETAIL_H
