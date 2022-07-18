/* AUTHOR: TIAN_SHENG, DATE: 2022/7/18 */
#include "vmarchcmd.h"
#include "color.h"

// cmdexec: (version)
// ===============
void vmarchcmd_exec_version(const struct vmarch_option_flags *p_optflags)
{
    printf("vmarch版本: %s1.0%s\n", VMARCH_COLOR_GREEN, VMARCH_COLOR_RESET);
}