/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchcmd.h"

#include <vector>
#include <unistd.h>
#include <iostream>
#include "cmdexec.h"

/* 遍历当前工作空间 */
void _iter_getcwd_files(std::vector<std::string> *cwdfvec)
{
    DIR *dir;
    struct dirent *ent;

    char curwd[_MAX_FILE_NAME];
    getcwd(curwd, sizeof ( curwd ));

    if ((dir = opendir(curwd)) == NULL) {
        fprintf(stderr, "-ERROR 打开工作目录%s失败。请检查目录是否存在", curwd);
        exit(-1);
    }

    while ((ent = readdir(dir)) != NULL)
        if (!_IGNORE_DIR(ent->d_name))
            cwdfvec->push_back(ent->d_name);

    closedir(dir);
}

/* 构建Java运行命令 */
void _execcmd_run_JVM(const std::string &server, const struct vmarch_option_flags *p_optflags)
{
    std::string runcmd = "nohup java";

    if (!striempty(p_optflags->dp))
        runcmd = runcmd + " -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=" + p_optflags->dp;

    runcmd = runcmd + " -jar " + server;

    if (!striempty(p_optflags->cp))
        runcmd = runcmd + " --spring.profiles.active=" +  p_optflags->cp;

    runcmd += " > logs.vmarch 2>&1 &";

    pcmdexec(runcmd.c_str());
}

/* 打印日志 */
void _execcmd_run_xtl(const std::string &server, const struct vmarch_option_flags *p_optflags)
{
    // cmdexec: (-tail)
    // ================
    if (p_optflags->xtl)
        pcmdexec("tail -f logs.vmarch");
}

// cmdexec: (start)
// ================
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags)
{
    std::vector<std::string> cwdfvec;       /* 当前工作目录下的所有文件名 */
    _iter_getcwd_files(&cwdfvec);

    // 查找 .jar 结尾的文件名
    std::vector<std::string> jarpacks;
    for (std::string &name : cwdfvec) {
        if (has_suffix(name, "jar"))
            jarpacks.push_back(name);
    }

    if (jarpacks.empty())
        throw std::runtime_error("没有查找到当前目录下的可运行JAR");

    std::string service = jarpacks[0];

    if (jarpacks.size() > 1) {
        printf("存在多个 JAR 文件，请根据序号选择要启动的服务: \n");

        int i = 0;
        for (auto &jarpack : jarpacks) {
            printf("  [%d] %s\n", i, jarpack.c_str());
            ++i;
        }

        unsigned seqnum;
        std::cin >> seqnum;
        service = jarpacks[seqnum];
    }

    /* 执行 Java 启动命令 */
    _execcmd_run_JVM(service, p_optflags);
    _execcmd_run_xtl(service, p_optflags);
}