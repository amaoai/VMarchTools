/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "declcmd.h"
#include "vps.h"
#include "cmdexec.h"
#include "vmarchtools.h"
#include <iostream>

void __vps(const std::string *pcmd, std::string *p_buf)
{
    std::string buf;
    rcmdexec(getps(pcmd->empty() ? "java" : pcmd->c_str()), &buf);
    p_buf->assign(buf);
}

void getvps_cmd(unsigned long pid, std::string *p_buf)
{
    rcmdexec(getps(std::to_string(pid), R"( for(i=11; i<(NF+1); i++) { printf "%s ", $i } )"), p_buf);
}

bool getvps_name(unsigned long pid, std::string *p_buf)
{
    std::string buf;
    rcmdexec(vmarchtools::fmt("jps -l | grep %d | awk '{printf \"%%s\", $2}'", pid), &buf);
    p_buf->assign(buf);
    return !buf.empty();
}

bool getvps_pid(const std::string &name, unsigned long *p_pid)
{
    std::string buf;
    rcmdexec(getps(name, R"( printf "%s,", $2 )"), &buf);\

    /* 如果PID不为空，删除结尾逗号 */
    if (!buf.empty())
        buf.pop_back();

    std::vector<std::string> pids = vmarchtools::split(buf, ",");
    if (pids.size() > 1) {
        printf("找到多个PID，请选择其中一个：\n");
        for (int i = 0; i < pids.size(); i++) {
            std::string cmd;
            getvps_cmd(vmarchtools::value_of<unsigned long>(pids[i]), &cmd);
            printf("[%d] %s %s\n", i + 1,pids[i].c_str(), cmd.c_str());
        }

        int idx;
        printf("请输入你要使用的PID序号：");
        std::cin >> idx;

        if (idx > pids.size())
            vmarchtools::verror("序号超出范围");

        buf.assign(pids[idx - 1]);
    }

    *p_pid = vmarchtools::value_of<unsigned long>(buf);
    return !buf.empty();
}

void cmd_vps(const std::string *pcmd, VMARCHFLAGS)
{
    std::string vps_buf;
    __vps(pcmd, &vps_buf);
    printf("%s\n", vps_buf.c_str());
}