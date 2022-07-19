/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#ifndef VMARCH_PROC_H
#define VMARCH_PROC_H

#include "typedef.h"

struct procinfo {
    char name[255];
    char pid[10];
    char port[10];
};

__VMARCH_API void getproc(const char *__Pid, struct procinfo *p_procinfo); /* 获取进程信息 */
__VMARCH_API void killproc(const char *__Pid); /* 杀掉进程 */

#endif /* VMARCH_PROC_H */
