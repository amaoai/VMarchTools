/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHTOOLS_H
#define VMARCH_VMARCHTOOLS_H

#include <string>
#include <tuple>

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )

namespace vmarchtools {
    std::string fmt(const char *__fmt, ...);
}

#endif /* VMARCH_VMARCHTOOLS_H */
