/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"

void vmarch_cmd_exec_start(std::string &pcmd, struct vmarch_start_flags *p_flags)
{
    std::string runcmd = "nohup java";

    if (!p_flags->vdb.empty())
        runcmd = runcmd + " -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=" + p_flags->vdb;

    runcmd = runcmd + " -jar " + "foxlibc.jar";

    if (!p_flags->cp.empty())
        runcmd = runcmd + " --spring.profiles.active=" +  p_flags->cp;

    runcmd += " > log.arch.tmp 2>&1 &";
}