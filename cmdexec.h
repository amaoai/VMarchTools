/* AUTHOR: TIAN_SHENG, DATE: 2022/7/20 */
#ifndef VMARCH_CMDEXEC_H
#define VMARCH_CMDEXEC_H

#include "typedef.h"

VMARCH_API void pcmdexec(const char *__Cmd); /* 执行cmd并打印输出 */
VMARCH_API char *rcmdexec(const char *__Cmd); /* 执行cmd获取输出结果 */
VMARCH_API void rcmdexec_free_buffer(char *__Buf); /* 释放 rcmdexec(__Cmd) 函数返回的缓冲 */

#endif /* VMARCH_CMDEXEC_H */
