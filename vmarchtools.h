/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHTOOLS_H
#define VMARCH_VMARCHTOOLS_H

#include <string>
#include "color.h"

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )
extern std::string check_java_file(const std::string *pcmd);

namespace vmarchtools {
    std::string vfmt(const std::string &__fmt, va_list __va);
    std::string fmt(const std::string &__fmt, ...);
    void verror(const std::string &__fmt, ...);
    void printf_to_stdout(const std::string &__fmt, ...);
    void printf_to_stderr(const std::string &__fmt, ...);
    bool is_number(const std::string &str);
    bool fread_all(const std::string &path, std::string *p_buf);
}

/* 打印红色背景的文本 */
#define VINFO_COLOR_BG_RED(m, ...) \
    vmarchtools::printf_to_stdout(VMARCH_COLOR_BG_RED VMARCH_COLOR_BOLD m VMARCH_COLOR_RESET VMARCH_COLOR_NORMAL, ##__VA_ARGS__)

#endif /* VMARCH_VMARCHTOOLS_H */
