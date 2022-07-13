/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchcmd.h"

/* 通过宏定义去调用命令 */
#define VMARCHCMDEXEC(name, p_optflags) vmarchcmd_exec_##name(p_optflags)

// cmdexec: (start)
// ================
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags)
{
    printf("exec: -start\n");
}

// cmdexec: (stop)
// ===============
void vmarchcmd_exec_stop(const struct vmarch_option_flags *p_optflags)
{
    printf("exec: -stop\n");
}

void vmarchcmd_exec(const struct vmarch_option_flags *p_optflags)
{
    if (p_optflags->cmd & VMARCHCMD_START)
        VMARCHCMDEXEC(start, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_STOP)
        VMARCHCMDEXEC(stop, p_optflags);
}