/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchcmd.h"

#include "jarfind.h"
#include "cmdexec.h"
#include <iostream>


/* 构建Java运行命令 */
void _execcmd_run_JVM(const std::string &server, const struct vmarch_option_flags *p_optflags)
{
    std::string runcmd = "nohup java";

    if (!striempty(p_optflags->dp))
        runcmd = runcmd + " -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=" + p_optflags->dp;

    runcmd = runcmd + " -jar " + server;

    if (!striempty(p_optflags->cp))
        runcmd = runcmd + " --spring.profiles.active=" +  p_optflags->cp;

    runcmd += " > log.arch.tmp 2>&1 &";

    pcmdexec(runcmd.c_str());
}

/* 打印日志 */
void _execcmd_run_xtl(const std::string &server, const struct vmarch_option_flags *p_optflags)
{
    // cmdexec: (-tail)
    // ================
    if (p_optflags->xtl)
        pcmdexec("tail -f log.arch.tmp");
}

// cmdexec: (start)
// ================
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags)
{
    std::string service = vmarch_getcwd_jarfile();

    /* 执行 Java 启动命令 */
    _execcmd_run_JVM(service, p_optflags);
    _execcmd_run_xtl(service, p_optflags);
}