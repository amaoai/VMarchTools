/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "vmarchcmd.h"

#include "cmd/declcmd.h"
#include "vmarchtools.h"
#include <stdexcept>

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

/**
 * 解析 start 或 restart 需要的选项
 */
void vmarchcmd_main_start(int argc, char **argv, struct vmarchcmd_flags *flags)
{
    int opt;
    while (getopts(argc, argv, vmarch_cmd_start_options, ARRAY_SIZE(vmarch_cmd_start_options), &opt) != -1) {
        switch (opt) {
            case OPTVAL_XTL: {
                flags->xtl = true;
                break;
            }
            case OPTVAL_VDB: {
                flags->vdb = atoi(xoptarg);
                break;
            }
            case OPTVAL_YML: {
                flags->yml = xoptarg;
                break;
            }
            case OPTVAL_HELP: {
                getopts_show_help("vmarch start help", vmarch_cmd_start_options, ARRAY_SIZE(vmarch_cmd_start_options));
                exit(EXIT_SUCCESS);
                break;
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
    if (has_cmd(cmd, VMARCHCMD_START, VMARCHCMD_RESTART)) {
        struct vmarchcmd_flags flags = {};
        vmarchcmd_main_start(argc, argv, &flags);

        if (cmd == VMARCHCMD_RESTART)
            cmd_stop(pcmd, VMARCHFLAGS_STOP_RESTART);

        cmd_start(pcmd, &flags, VMARCHFLAGS_NO_FALGS);
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

UNKNOWN_COMMAND:
    if (cmd == 0)
        throw std::runtime_error("unknown command " + cmdstr);

    if (argc >= 3)
        if (argv[2] != nullptr && argv[2][0] != '-')
            pcmd->assign(argv[2]);

    return cmd;
}

void vmarchcmd_main(int argc, char **argv)
{
    if (argc < 2)
        throw std::runtime_error("no command");

    std::string pcmd;
    VMARCHCMD cmd = getcmd(argc, argv, &pcmd);

    if (has_cmd(cmd, VMARCHCMD_START, VMARCHCMD_RESTART))
        have_args_cmd_main(cmd, &pcmd, argc, argv);

    if (has_cmd(cmd, VMARCHCMD_STOP, VMARCHCMD_PS))
        no_args_cmd_main(cmd, &pcmd, argc, argv);

}