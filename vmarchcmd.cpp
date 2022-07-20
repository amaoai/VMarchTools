/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include "opts.h"
#include <string>
#include <cstring>

#define OPT_XTL (1)
#define OPT_CP  (2)
#define OPT_VDB (3)

const static struct option VMARCH_START_RESTART_OPTIONS[] = {
        {"", "xtl", no_argument,       OPT_XTL, "打印启动日志"},
        {"", "cp",  required_argument, OPT_CP,  "指定服务配置文件后缀"},
        {"", "vdb", required_argument, OPT_VDB, "远程调试端口"},
};

/* 使用帮助提示语 */
#define VMARCH_HELP "vmarch usage: [ <start | restart> -xtl -cp -vdp ... ] [ stop ] [ ps ] \n" \
                            "       [ package <docker, ...> ] [ --help ]"

/* 函数定义 */
void vmarch_cmd_main_start(const char *cmd, std::string &pcmd, int argc, char **argv);
void vmarch_cmd_main_ps(const char *cmd, std::string &pcmd, int argc, char **argv);
void vmarch_cmd_main_stop(const char *cmd, std::string &pcmd, int argc, char **argv);
void vmarch_cmd_exec_start(std::string &pcmd, struct vmarch_start_flags *flags);
void vmarch_cmd_exec_stop(std::string &pcmd);
void vmarch_cmd_exec_ps(std::string &pcmd);

/* 开始解析命令 */
void vmarch_cmd_main(int argc, char **argv)
{
    char        *cmd;
    std::string  pcmd;

    if (argc == 1)
        verror("%s\n", VMARCH_HELP);

    cmd = argv[1];

    if (argv[2] != NULL && strlen(argv[2]) > 0) {
        if (argv[2][0] != '-')
            pcmd = argv[2];
    }

    if (strcmp("start", cmd) == 0 || strcmp("restart", cmd) == 0)
        vmarch_cmd_main_start(cmd, pcmd, argc, argv);

    if (strcmp("stop", cmd) == 0)
        vmarch_cmd_main_stop(cmd, pcmd, argc, argv);

    if (strcmp("ps", cmd) == 0)
        vmarch_cmd_main_ps(cmd, pcmd, argc, argv);
}

void vmarch_cmd_main_start(const char *cmd, std::string &pcmd, int argc, char **argv)
{
    int                         opt;
    struct vmarch_start_flags   flags;

    while (getopts(argc, argv, VMARCH_START_RESTART_OPTIONS, sizeof(VMARCH_START_RESTART_OPTIONS), &opt) != -1) {
        switch (opt) {
            case OPT_XTL: flags.xtl = true; break;
            case OPT_CP: flags.cp = xoptarg; break;
            case OPT_VDB: flags.vdb = xoptarg; break;
            case OPT_UNKNOWN: verror("未知选项: %s\n", xoptopt);
        }
    }

    if (strcmp("restart", cmd) == 0)
        vmarch_cmd_exec_stop(pcmd);

    vmarch_cmd_exec_start(pcmd, &flags);
}

void vmarch_cmd_main_stop(const char *cmd, std::string &pcmd, int argc, char **argv)
{
    int                         opt;

    while (getopts(argc, argv, VMARCH_START_RESTART_OPTIONS, sizeof(VMARCH_START_RESTART_OPTIONS), &opt) != -1) {
        switch (opt) {
            case OPT_UNKNOWN: verror("未知选项: %s\n", xoptopt);
        }
    }

    vmarch_cmd_exec_stop(pcmd);
}

void vmarch_cmd_main_ps(const char *cmd, std::string &pcmd, int argc, char **argv)
{
    int                         opt;

    while (getopts(argc, argv, VMARCH_START_RESTART_OPTIONS, sizeof(VMARCH_START_RESTART_OPTIONS), &opt) != -1) {
        switch (opt) {
            case OPT_UNKNOWN: verror("未知选项: %s\n", xoptopt);
        }
    }

    vmarch_cmd_exec_ps(pcmd);
}