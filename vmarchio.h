/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#ifndef VMARCH_VMARCHIO_H
#define VMARCH_VMARCHIO_H

#include "typedef.h"
#include <stdlib.h>

/* 是不是忽略目录 . 和 .. */
#define _IGNORE_DIR(name) (              \
    (name[0] == '.' ||                   \
     name[0] == '.' && name[1] == '.')   \
    && name[2] == '\0' )

struct VMARCHFILE_T;
#define VMARCHFILE struct VMARCHFILE_T

/* 文件结构体 */
struct VMARCHFILE_T {
    char name[_MAX_FILE_NAME];
    BOOL dir;
};

VMARCH_API VMARCHFILE *ls(char *path, int *size);   /* 遍历文件目录 */
VMARCH_API void vmarchio_free_files(VMARCHFILE *);

#endif /* VMARCH_VMARCHIO_H */
