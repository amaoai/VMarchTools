/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include <string>
#include "proc.h"

// cmdexec: (ps)
// ================
void vmarch_cmd_exec_ps(std::string &pcmd)
{
    std::string xpsval;
    proc_exec("xps", pcmd, xpsval);
    printf("%s\n", xpsval.c_str());
}