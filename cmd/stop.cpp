/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "declcmd.h"
#include "vps.h"
#include "vmarchtools.h"
#include "cmdexec.h"

extern std::string check_file(const std::string *pcmd);

void cmd_stop(const std::string *pcmd, VMARCHFLAGS vflags)
{
    std::string pid;
    auto jfile = check_file(pcmd);

    if (!getvps_pid(jfile, &pid)) {
        if (vflags & VMARCHFLAGS_STOP_RESTART)
            return;
        vmarchtools::verror("PID不存在或已经被杀掉");
    }

    std::string name;
    if (!getvps_name(pid, &name))
        vmarchtools::verror("进程名不存在或已经被杀掉，PID=%s", pid.c_str());

    pcmdexec(vmarchtools::fmt("kill -9 %s", pid.c_str()));
    VINFO_COLOR_BG_RED("已杀死进程【%s/%s】\n", pid.c_str(), name.c_str());
}