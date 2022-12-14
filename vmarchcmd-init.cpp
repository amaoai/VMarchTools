/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "vmarchcmd.h"

#include "cmd/declcmd.h"
#include "vmarchtools.h"

/**
 * 判断是否存在某个命令，比如：has_cmd(cmd_val, "help", "stop", ...)
 * 判断 cmd_val 是否包含 help、stop、...
 */
template<typename... Args>
uint64_t has_cmd(VMARCHCMD cmd, Args... va_list)
{
    for (auto &arg : {va_list...}) {
        if (cmd == arg) {
            return true;
        }
    }

    return false;
}

#define VMARCGTOOLS_MESSAGE "" \
                "无参命令: \n" \
                "  - ps         显示当前系统中正在运行的Java进程（不包括容器）\n" \
                "  - stop       停止当前正在运行的Java进程，需要到jar包目录执行。或者直接输入进程名\n" \
                "\n" \
                "带参命令: \n" \
                "  - start      启动Java进程，需要到jar包目录执行。\n" \
                "  - restart    重启Java进程，需要到jar包目录执行。\n" \
                "  - status     显示进程状态，（需要到jar包目录执行或输入进程名）\n"\
                "\n"           \
                "命令参数详情请使用 vmarch <command> -h 查看"

/* 解析 start 或 restart 需要的选项 */
void vmarchcmd_main_parse_start(int argc, char **argv, struct vmarchcmd_flags *flags)
{
    int opt;
    while (getopts(argc, argv, vmarch_cmd_start_options, ARRAY_SIZE(vmarch_cmd_start_options), &opt) != -1) {
        switch (opt) {
            case OPTVAL_START_XTL: {
                flags->xtl = true;
                break;
            }
            case OPTVAL_START_VDB: {
                flags->vdb = vmarchtools::value_of<int>(xoptarg);
                break;
            }
            case OPTVAL_START_YML: {
                flags->yml = xoptarg;
                break;
            }
            case OPTVAL_START_CP: {
                flags->cp = xoptarg;
                break;
            }
            case OPTVAL_HELP: {
                getopts_show_help("vmarch start help", vmarch_cmd_start_options, ARRAY_SIZE(vmarch_cmd_start_options));
                exit(EXIT_SUCCESS);
            }
            case OPT_UNKNOWN:
                verror_unknown_cmd(xoptopt);
        }
    }
}

/* 解析 status 需要的选项 */
void vmarchcmd_main_parse_status(int argc, char **argv, struct vmarchcmd_flags *flags)
{
    int opt;
    while (getopts(argc, argv, vmarch_cmd_status_options, ARRAY_SIZE(vmarch_cmd_status_options), &opt) != -1) {
        switch (opt) {
            case OPTVAL_STATUS_DETAIL: {
                flags->detail = xoptarg == NULL ? "/status" : xoptarg;
                break;
            }
            case OPTVAL_STATUS_NETWORK: {
                flags->network = true;
                break;
            }
            case OPTVAL_STATUS_THREADS: {
                flags->threads = true;
                break;
            }
            case OPTVAL_HELP: {
                getopts_show_help("vmarch start help", vmarch_cmd_status_options, ARRAY_SIZE(vmarch_cmd_status_options));
                exit(EXIT_SUCCESS);
            }
            case OPT_UNKNOWN:
                verror_unknown_cmd(xoptopt);
        }
    }
}

/**
 * 解析有选项的命令
 */
void have_args_cmd_main(VMARCHCMD cmd, std::string *pcmd, int argc, char **argv)
{
    struct vmarchcmd_flags flags = {};

    if (has_cmd(cmd, VMARCHCMD_START, VMARCHCMD_RESTART)) {
        vmarchcmd_main_parse_start(argc, argv, &flags);

        if (cmd == VMARCHCMD_RESTART)
            cmd_stop(pcmd, VMARCHFLAGS_STOP_RESTART);

        cmd_start(pcmd, &flags, VMARCHFLAGS_NO_FALGS);
    }

    if (cmd == VMARCHCMD_STATUS) {
        vmarchcmd_main_parse_status(argc, argv, &flags);
        cmd_status(pcmd, &flags, VMARCHFLAGS_NO_FALGS);
    }

}

/**
 * 解析无选项的命令
 */
void no_args_cmd_main(VMARCHCMD cmd, std::string *pcmd, int argc, char **argv)
{
    int opt;
    while (getopts(argc, argv, vmarch_cmd_start_options, ARRAY_SIZE(vmarch_cmd_start_options), &opt) != -1) {
        switch (opt) {
            case OPT_UNKNOWN:
                verror_unknown_cmd(xoptopt);
        }
    }

    if (cmd == VMARCHCMD_PS)
        cmd_vps(pcmd, VMARCHFLAGS_NO_FALGS);

    if (cmd == VMARCHCMD_STOP)
        cmd_stop(pcmd, VMARCHFLAGS_STOP_JUST_STOP);
}

VMARCHCMD getcmd(int argc, char **argv, std::string *pcmd)
{
    std::string cmdstr = argv[1];
    VMARCHCMD   cmd = 0;

    if (cmdstr[0] == '-')
        goto UNKNOWN_COMMAND;

    if (cmdstr == "start") cmd = VMARCHCMD_START;
    if (cmdstr == "restart") cmd = VMARCHCMD_RESTART;
    if (cmdstr == "stop") cmd = VMARCHCMD_STOP;
    if (cmdstr == "ps") cmd = VMARCHCMD_PS;
    if (cmdstr == "status") cmd = VMARCHCMD_STATUS;

UNKNOWN_COMMAND:
    if (cmd == 0)
        verror_unknown_cmd(cmdstr.c_str());

    if (argc >= 3)
        if (argv[2] != nullptr && argv[2][0] != '-')
            pcmd->assign(argv[2]);

    return cmd;
}

void vmarchcmd_main(int argc, char **argv)
{
    if (argc < 2)
        vmarchtools::verror(VMARCGTOOLS_MESSAGE);

    std::string pcmd;
    VMARCHCMD cmd = getcmd(argc, argv, &pcmd);

    if (has_cmd(cmd, VMARCHCMD_START, VMARCHCMD_RESTART, VMARCHCMD_STATUS))
        have_args_cmd_main(cmd, &pcmd, argc, argv);

    if (has_cmd(cmd, VMARCHCMD_STOP, VMARCHCMD_PS))
        no_args_cmd_main(cmd, &pcmd, argc, argv);

}