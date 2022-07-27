/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHTOOLS_H
#define VMARCH_VMARCHTOOLS_H

#include <cstdarg>
#include <string>

#define __VMARCHTOOLS_NAMESPACE_START namespace vmarchtools {
#define __VMARCHTOOLS_NAMESPACE_END }

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )

__VMARCHTOOLS_NAMESPACE_START
std::string vfmt(const char *__fmt, va_list va);
std::string fmt(const char *__fmt, ...);
void verror(const char *__fmt, ...);
__VMARCHTOOLS_NAMESPACE_END
#endif /* VMARCH_VMARCHTOOLS_H */
