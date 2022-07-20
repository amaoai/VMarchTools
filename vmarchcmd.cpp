/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include "opts.h"
#include <string>
#include <cstring>
#include <stdarg.h>
#include <tuple>

#define CMD_START       (1 << 0)
#define CMD_RESTART     (1 << 1)
#define CMD_STOP        (1 << 2)
#define CMD_PS          (1 << 3)
#define CMD_DUMP        (1 << 4)

#define VMARCHCMD       unsigned

#define OPT_XTL (1)
#define OPT_CP  (2)
#define OPT_VDB (3)

inline static bool __vmarch_has_cmd(VMARCHCMD cmd0, int len, ...)
{
    va_list ap;
    va_start(ap, len);
    for (int i = 0; i < len; i++)
        if (va_arg(ap, VMARCHCMD) == cmd0)
            return true;
    va_end(ap);

    return false;
}

#define VA_ARGS_COUNT(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value
#define has_cmd(cmd, ...) __vmarch_has_cmd(cmd, VA_ARGS_COUNT(__VA_ARGS__), ##__VA_ARGS__)

const static struct option VMARCH_START_RESTART_OPTIONS[] = {
        {"", "xtl", no_argument,       OPT_XTL, "打印启动日志"},
        {"", "cp",  required_argument, OPT_CP,  "指定服务配置文件后缀"},
        {"", "vdb", required_argument, OPT_VDB, "远程调试端口"},
};

/* 使用帮助提示语 */
#define VMARCH_HELP "vmarch usage: [ <start | restart> -xtl -cp -vdp ... ] [ stop ] [ ps ] \n" \
                    "              [ package <docker, ...> ] [ dump ] [ --help ]"

/* 函数定义 */
void vmarch_cmd_main_start(VMARCHCMD cmd, std::string &pcmd, int argc, char **argv);
void vmarch_cmd_main_no_opt(VMARCHCMD cmd, std::string &pcmd, int argc, char **argv);
void vmarch_cmd_exec_start(std::string &pcmd, struct vmarch_start_flags *flags);
void vmarch_cmd_exec_stop(std::string &pcmd);
void vmarch_cmd_exec_ps(std::string &pcmd);

/* 获取执行命令 */
std::string getcmd(int argc, char **argv, VMARCHCMD *cmd)
{
    std::string pcmd = "";

    if (argc == 1)
        verror("%s\n", VMARCH_HELP);

    if (strcmp("start", argv[1]) == 0)
        *cmd = CMD_START;

    if (strcmp("restart", argv[1]) == 0)
        *cmd = CMD_RESTART;

    if (strcmp("stop", argv[1]) == 0)
        *cmd = CMD_STOP;

    if (strcmp("ps", argv[1]) == 0)
        *cmd = CMD_PS;

    if (strcmp("dump", argv[1]) == 0)
        *cmd = CMD_DUMP;

    /* 获取 cmd 参数 */
    if (argv[2] != NULL && strlen(argv[2]) > 0) {
        if (argv[2][0] != '-')
            pcmd = argv[2];
    }

    return pcmd;
}

/* 开始解析命令 */
void vmarch_cmd_main(int argc, char **argv)
{
    VMARCHCMD    cmd;
    std::string  pcmd;

    pcmd = getcmd(argc, argv, &cmd);

    if (has_cmd(cmd, CMD_START, CMD_RESTART))
        vmarch_cmd_main_start(cmd, pcmd, argc, argv);

    if (has_cmd(cmd, CMD_STOP, CMD_PS, CMD_DUMP))
        vmarch_cmd_main_no_opt(cmd, pcmd, argc, argv);
}

void vmarch_cmd_main_start(VMARCHCMD cmd, std::string &pcmd, int argc, char **argv)
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

    if (cmd == CMD_RESTART)
        vmarch_cmd_exec_stop(pcmd);

    vmarch_cmd_exec_start(pcmd, &flags);
}

void vmarch_cmd_main_no_opt(VMARCHCMD cmd, std::string &pcmd, int argc, char **argv)
{
    int                         opt;

    while (getopts(argc, argv, VMARCH_START_RESTART_OPTIONS, sizeof(VMARCH_START_RESTART_OPTIONS), &opt) != -1) {
        switch (opt) {
            case OPT_UNKNOWN: verror("未知选项: %s\n", xoptopt);
        }
    }

    switch (cmd) {
        case CMD_PS: vmarch_cmd_exec_ps(pcmd); break;
        case CMD_STOP: vmarch_cmd_exec_stop(pcmd); break;
    }
}