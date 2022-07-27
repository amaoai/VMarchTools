/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHTOOLS_H
#define VMARCH_VMARCHTOOLS_H

#include <string>

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )

namespace vmarchtools {
    std::string vfmt(const std::string &__fmt, va_list __va);
    std::string fmt(const std::string &__fmt, ...);
    void verror(const std::string &__fmt, ...);
    void printf_to_stdout(const std::string &__fmt, ...);
    void printf_to_stderr(const std::string &__fmt, ...);
}
#endif /* VMARCH_VMARCHTOOLS_H */
