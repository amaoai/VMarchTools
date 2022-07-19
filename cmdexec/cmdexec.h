/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#ifndef VMARCH_SYSEXEC_H
#define VMARCH_SYSEXEC_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int rcmdexec(const char *__Cmd, char *__Buf, size_t __BufSiz); /* 执行命令并获取执行后的命令行缓冲 */
int pcmdexec(const char *__Cmd); /* 执行命令并打印 */

#ifdef __cplusplus
};
#endif

#endif /* VMARCH_SYSEXEC_H */
