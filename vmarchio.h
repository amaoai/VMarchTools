/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#ifndef VMARCH_VMARCHIO_H
#define VMARCH_VMARCHIO_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>

#define _IGNORE_DIR(ch) ( (ch[0] == '.' || (ch[0] == '.' && ch[1] == '.')) \
    && ch[2] == '\0' )

/* 判断文件后缀 */
static inline bool has_suffix(const std::string &__filename, const std::string &__sufx)
{
    size_t index = __filename.find(__sufx, __filename.size() - __sufx.size());
    return ( index != std::string::npos );
}

#endif /* VMARCH_VMARCHIO_H */
