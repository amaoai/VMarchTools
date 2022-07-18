/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#ifndef VMARCH_SYSEXEC_H
#define VMARCH_SYSEXEC_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*__func_read_buf)(const char *__Buf);
static inline void __DefCallbackPrintBuf(const char *__Buf)
  { printf("%s", __Buf); }
/* 执行命令行 */
int __fcmdexec(const char *, __func_read_buf);
#define pcmdexec(__Cmd) __fcmdexec((__Cmd), __DefCallbackPrintBuf)   /* 执行命令并打印缓冲 */
void rcmdexec(const char *__Cmd, char *__Buf, size_t __BufSiz);      /* 执行命令并获取执行后的命令行缓冲 */

#ifdef __cplusplus
};
#endif

#endif /* VMARCH_SYSEXEC_H */
