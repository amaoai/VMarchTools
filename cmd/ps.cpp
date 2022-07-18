/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#include "vmarchcmd.h"

#include "cmdexec.h"
#include "color.h"

// cmdexec: (ps)
// ================
void vmarchcmd_exec_ps(const struct vmarch_option_flags *p_optflags)
{
    char cmdbuf[0xFFFF];
    rcmdexec("ps -ef | grep java", cmdbuf, sizeof(cmdbuf));
    printf("%s", cmdbuf);
    printf("%s --> buf size: %zu, length: %zu <-- %s\n", VMARCH_COLOR_RED, sizeof(cmdbuf), strlen(cmdbuf), VMARCH_COLOR_RESET);
}