/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHTOOLS_H
#define VMARCH_VMARCHTOOLS_H

#include "color.h"
#include <string>
#include <vector>
#include <sstream>

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )
extern std::string check_java_file(const std::string *pcmd);

namespace vmarchtools {
    std::string vfmt(const std::string &__fmt, va_list __va); /* va_list格式化 */
    std::string fmt(const std::string &__fmt, ...); /* 字符串格式化 */
    void verror(const std::string &__fmt, ...); /* 程序中断错误 */
    void printf_to_stdout(const std::string &__fmt, ...); /* 打印标准 */
    bool is_number(const std::string &str); /* 判断字符串是不是数字 */
    void fread_all(const std::string &path, std::string *p_buf); /* 可能不适用于vfs文件系统中的文件 */
    std::vector<std::string> split(const std::string &str, const std::string &delim); /* 分割字符串 */
    template <typename T>
      T value_of(const std::string &str) /* 字符串转其他类型 */
    {
        std::stringstream ss(str);
        T ret;
        ss >> ret;
        return ret;
    }
}

/* 打印红色背景的文本到标准IO */
#define VINFO_COLOR_BG_RED(m, ...) \
    printf(VMARCH_COLOR_BG_RED VMARCH_COLOR_BOLD m VMARCH_COLOR_RESET VMARCH_COLOR_NORMAL, ##__VA_ARGS__)
/* 打印蓝色背景的文本到标准IO */
#define VINFO_COLOR_BG_BLUE(m, ...) \
    printf(VMARCH_COLOR_BG_BLUE VMARCH_COLOR_BOLD m VMARCH_COLOR_RESET VMARCH_COLOR_NORMAL, ##__VA_ARGS__)
/* 打印绿色背景的文本到标准IO */
#define VINFO_COLOR_BG_GREEN(m, ...) \
    printf(VMARCH_COLOR_BG_GREEN VMARCH_COLOR_BOLD m VMARCH_COLOR_RESET VMARCH_COLOR_NORMAL, ##__VA_ARGS__)

#endif /* VMARCH_VMARCHTOOLS_H */
