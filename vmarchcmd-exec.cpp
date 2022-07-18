/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchcmd.h"

/* 定义命令执行函数 */
#define VMARCH_DEFINE_CMD_CALL(name) \
    void vmarchcmd_exec_##name(const struct vmarch_option_flags *)

VMARCH_API VMARCH_DEFINE_CMD_CALL(start);
VMARCH_API VMARCH_DEFINE_CMD_CALL(stop);
VMARCH_API VMARCH_DEFINE_CMD_CALL(restart);
VMARCH_API VMARCH_DEFINE_CMD_CALL(ps);
VMARCH_API VMARCH_DEFINE_CMD_CALL(dump);
VMARCH_API VMARCH_DEFINE_CMD_CALL(exec);
VMARCH_API VMARCH_DEFINE_CMD_CALL(pak);
VMARCH_API VMARCH_DEFINE_CMD_CALL(version);

/* 通过宏定义去调用命令 */
#define vmarch_cmd_exec(name, p_optflags) vmarchcmd_exec_##name(p_optflags)

/* 执行命令 */
void vmarchcmd_exec(const struct vmarch_option_flags *p_optflags)
{
    if (p_optflags->cmd & VMARCHCMD_START)
        vmarch_cmd_exec(start, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_STOP)
        vmarch_cmd_exec(stop, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_RESTART) {
        vmarch_cmd_exec(stop, p_optflags);
        vmarch_cmd_exec(start, p_optflags);
    }

    if (p_optflags->cmd & VMARCHCMD_PS)
        vmarch_cmd_exec(ps, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_DUMP)
        vmarch_cmd_exec(dump, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_EXEC)
        vmarch_cmd_exec(exec, p_optflags);

    if (p_optflags->cmd & VMARCHCMD_PAK)
        vmarch_cmd_exec(pak, p_optflags);

    if (p_optflags->v)
        vmarch_cmd_exec(version, p_optflags);
}