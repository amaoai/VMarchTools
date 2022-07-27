/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "vmarchtools.h"
#include <stdexcept>
__VMARCHTOOLS_NAMESPACE_START

std::string vfmt(const char *__fmt, va_list va)
{
    char *buf;
    int len;
    len = vasprintf(&buf, __fmt, va);
    std::string __fmtret(buf, len);
    free(buf);

    return __fmtret;
}

std::string fmt(const char *__fmt, ...)
{
    va_list va;
    va_start(va, __fmt);
    std::string __fmtret = vfmt(__fmt, va);
    va_end(va);

    return __fmtret;
}

void verror(const char *__fmt, ...)
{
    va_list va;
    va_start(va, __fmt);
    throw std::runtime_error(vfmt(__fmt, va));
    va_end(va);
}

__VMARCHTOOLS_NAMESPACE_END