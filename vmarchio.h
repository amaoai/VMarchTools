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

VMARCH_API void getpwd(char *__Buf, size_t __Size); /* 获取当前文件执行目录 */
VMARCH_API void find(const char *__Path, const char *__Cond, std::vector<std::string> *); /* 查找文件 */
VMARCH_API void getexedir(char *__Buf); /* 获取自身目录所在路径 */
VMARCH_API void getparent(const char *__Path, char *__Buf); /* 获取上一级目录 */

/* 判断文件后缀 */
static inline bool has_suffix(const std::string &__filename, const std::string &__sufx)
{
    size_t index = __filename.find(__sufx, __filename.size() - __sufx.size());
    return ( index != std::string::npos );
}

#endif /* VMARCH_VMARCHIO_H */
