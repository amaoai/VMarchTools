/* AUTHOR: TIAN_SHENG, DATE: 2022/7/12 */
#ifndef VMARCH_CMD_INIT_H
#define VMARCH_CMD_INIT_H

#include "vmarchcmd-core.h"
#include <string.h>

#define _VMARCH_THROW_ERROR(...) { fprintf(stderr, __VA_ARGS__); exit(-1); }

/* 执行命令 */
void vmarchcmd_exec(const struct vmarch_option_flags *p_optflags);

#endif /* VMARCH_CMD_INIT_H */
