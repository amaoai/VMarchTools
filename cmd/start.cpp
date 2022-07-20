/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include "vmarchio.h"
#include <iostream>

std::string getexecfile()
{
    int seq = 1;

    /* 查询当前目录下的可执行文件 */
    char cwd[PATH_MAX];
    getpwd(cwd, sizeof(PATH_MAX));

    std::vector<std::string> exefvec;
    find(cwd, "-name *.jar -o -name *.war", &exefvec);

    size_t exefvec_size = exefvec.size();
    if (exefvec_size > 1) {
        for (int i = 0; i < exefvec_size; i++) {
            printf("  [%d] - %s\n", (i + 1), exefvec[i].c_str());
        }

        printf("请根据序号选择启动服务（输入无效序号退出程序）:");

        std::cin >> seq;

        if (seq <= 0 || seq > exefvec_size)
            exit(0);
    }

    return exefvec[(seq - 1)];
}

void vmarch_cmd_exec_start(std::string &pcmd, struct vmarch_start_flags *p_flags)
{
    /* 执行命令 */
    std::string runcmd = "nohup java";

    if (!p_flags->vdb.empty())
        runcmd = runcmd + " -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=" + p_flags->vdb;

    std::string jarfile;

    if (!pcmd.empty()) {
        jarfile = pcmd;
    } else {
        jarfile = getexecfile();
    }

    runcmd = runcmd + " -jar " + jarfile;

    if (!p_flags->cp.empty())
        runcmd = runcmd + " --spring.profiles.active=" +  p_flags->cp;

    runcmd += " > log.vmarch.tmp 2>&1 &";

    pcmdexec(runcmd.c_str());

    if (p_flags->xtl)
        pcmdexec("tail -f log.vmarch.tmp");
}