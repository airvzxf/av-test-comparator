#ifndef AV_TEST_COMPARATOR_CORE_WINDOWS_PC_CSV_EXPORT_H
#define AV_TEST_COMPARATOR_CORE_WINDOWS_PC_CSV_EXPORT_H

#include <string>
#include "../../../structure/antivirus.h"

namespace core::windows::pc::csv {
    void exportFrom(std::vector<core::structure::antivirus> &catalog, const std::string &filename);
}
#endif //AV_TEST_COMPARATOR_CORE_WINDOWS_PC_CSV_EXPORT_H
