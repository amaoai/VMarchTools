/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "declcmd.h"
#include "vps.h"
#include "vmarchtools.h"
#include "cmdexec.h"

void cmd_stop(const std::string *pcmd, VMARCHFLAGS vflags)
{
    unsigned long pid;
    auto jfile = check_java_file(pcmd);

    if (!getvps_pid(jfile, &pid)) {
        if (vflags & VMARCHFLAGS_STOP_RESTART)
            return;
        vmarchtools::verror("PID不存在或已经被杀掉");
    }

    std::string name;
    if (!getvps_name(pid, &name))
        vmarchtools::verror("进程不存在或有多个（如果PID很长就是多个PID组合起来的），PID=%lu", pid);

    pcmdexec(vmarchtools::fmt("kill -9 %lu", pid));
    VINFO_COLOR_BG_RED("已杀死进程【%lu/%s】\n", pid, name.c_str());
}