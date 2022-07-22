/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include <unordered_map>
#include <sstream>
#include <string>
#include "color.h"

inline static void proc_exec_xps(const std::string &pcmd)
{
    pcmdexec("bash ../sh/xps ");
}

// cmdexec: (ps)
// ================
void vmarch_cmd_exec_ps(std::string &pcmd)
{
    proc_exec_xps(pcmd);
}