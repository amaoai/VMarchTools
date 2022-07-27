/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "vps.h"
#include "cmdexec.h"
#include "vmarchtools.h"

void __vps(const std::string *pcmd, std::string *p_buf)
{
    rcmdexec(vmarchtools::fmt("ps -ef | grep %s | grep -v grep | grep -v vmarch",
                              pcmd->empty() ? "java" : pcmd->c_str()), p_buf);
}

bool getvps_name(const std::string &pid, std::string *p_buf)
{
    std::string buf;
    rcmdexec(vmarchtools::fmt("jps -l | grep %s | awk '{printf \"%%s\", $2}'", pid.c_str()), &buf);
    p_buf->assign(buf);
    return !buf.empty();
}

bool getvps_pid(const std::string &name, std::string *p_buf)
{
    std::string buf;
    rcmdexec(vmarchtools::fmt("ps -ef | grep %s | grep -v grep | grep -v vmarch | awk '{printf \"%%s\", $2}'",
                              name.c_str()), &buf);
    p_buf->assign(buf);
    return !buf.empty();
}

void cmd_vps(const std::string *pcmd)
{
    std::string vps_buf;
    __vps(pcmd, &vps_buf);
    vmarchtools::printf_to_stdout(vps_buf);
}