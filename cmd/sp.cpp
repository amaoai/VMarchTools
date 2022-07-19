/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"

// cmdexec: (-sp)
// ================
void vmarchcmd_exec_sp(const struct vmarch_option_flags *p_optflags)
{
    char __Cmd[255] = {};
    sprintf(__Cmd, "netstat -tlnp | awk '$7~/^'\"%s\"'\\/.*?$/ {print $4}'", p_optflags->sp);
    pcmdexec(__Cmd, false);
}