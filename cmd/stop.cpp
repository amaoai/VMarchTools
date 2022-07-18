/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchcmd.h"

#include "color.h"
#include "jarfind.h"

// cmdexec: (stop)
// ===============
void vmarchcmd_exec_stop(const struct vmarch_option_flags *p_optflags)
{
    std::string jarfile = vmarch_getcwd_jarfile();

    char __Buf[0x2FF0];
    rcmdexec(("vmarch ps | grep " + jarfile).c_str(), __Buf, sizeof(__Buf));

    std::string pid(__Buf);
    std::remove(pid.begin(), pid.end(), ' ');
    pid = pid.substr(1, pid.find("]") - 1);

    printf("%s", __Buf);
    pcmdexec(("kill -9 " + pid).c_str());
}