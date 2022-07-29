/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "declcmd.h"
#include "vps.h"
#include "cmdexec.h"
#include "vmarchtools.h"
#include <iostream>
#include <unordered_map>

void __vps(const std::string *pcmd, std::string *p_buf)
{
    std::string buf;
    rcmdexec(getps(pcmd->empty() ? "java" : pcmd->c_str()), &buf);

    p_buf->assign(buf);
}

void getvps_cmd(const std::string &pid, std::string *p_buf)
{
    rcmdexec(getps(pid, R"( for(i=11; i<(NF+1); i++) { printf "%s ", $i } )"), p_buf);
    p_buf->pop_back();
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
    rcmdexec(getps(name, R"( printf "%s,", $2 )"), &buf);

    if (!buf.empty())
        buf.pop_back();

    std::vector<std::string> pids = vmarchtools::split(buf, ",");
    if (pids.size() > 1) {
        vmarchtools::printf_to_stdout("找到多个PID，请选择其中一个：\n");
        for (int i = 0; i < pids.size(); i++) {
            std::string cmd;
            getvps_cmd(pids[i], &cmd);
            vmarchtools::printf_to_stdout("[%d] %s %s\n", i + 1,pids[i].c_str(), cmd.c_str());
        }

        int idx;
        vmarchtools::printf_to_stdout("请输入你要使用的PID序号：");
        std::cin >> idx;

        if (idx > pids.size())
            vmarchtools::verror("序号超出范围！");

        buf.assign(pids[idx - 1]);
    }

    p_buf->assign(buf);
    return !buf.empty();
}

void cmd_vps(const std::string *pcmd, VMARCHFLAGS)
{
    std::string vps_buf;
    __vps(pcmd, &vps_buf);
    vmarchtools::printf_to_stdout(vps_buf);
}