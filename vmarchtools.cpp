/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "vmarchtools.h"
#include <cstdarg>

namespace vmarchtools {
    std::string fmt(const char *__fmt, ...) {
        char *buf;
        int len;
        va_list va;

        va_start(va, __fmt);
        len = vasprintf(&buf, __fmt, va);
        va_end(va);

        std::string __fmtret(buf, len);
        free(buf);

        return __fmtret;
    }
}