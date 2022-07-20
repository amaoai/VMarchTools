/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#ifndef VMARCH_VMARCHIO_H
#define VMARCH_VMARCHIO_H

#include "typedef.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>

#define _IGNORE_DIR(ch) ( (ch[0] == '.' || (ch[0] == '.' && ch[1] == '.')) \
    && ch[2] == '\0' )

VMARCH_API void getpwd(char *__Buf, size_t __Size); /* 获取当前工作目录 */
VMARCH_API void find(const char *__Path, const char *__Condi,
                     std::vector<std::string> *); /* 查找文件 */

/* 判断文件后缀 */
static inline bool has_suffix(const std::string &__filename, const std::string &__sufx)
{
    size_t index = __filename.find(__sufx, __filename.size() - __sufx.size());
    return ( index != std::string::npos );
}

#endif /* VMARCH_VMARCHIO_H */
