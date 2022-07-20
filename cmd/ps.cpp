/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include <unordered_map>
#include "color.h"

// cmdexec: (ps)
// ================
void vmarch_cmd_exec_ps(std::string &pcmd)
{
    char *p_buf = rcmdexec("ps -aux");
    printf("%s%s%s\n", VMARCH_COLOR_BG_RED, p_buf, VMARCH_COLOR_RESET);
    rcmdexec_free_buffer(p_buf);
}