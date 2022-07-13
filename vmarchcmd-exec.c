/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchcmd.h"
#include "vmarchio.h"

/* 通过宏定义去调用命令 */
#define vmarchcmdexec(name, p_optflags) vmarchcmd_exec_##name(p_optflags)

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
        vmarchcmdexec(start, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_STOP)
        vmarchcmdexec(stop, p_optflags);
}