/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include "vmarchcmd.h"

#define VMARCH_ERROR_OUT_OF_INDEX(cmd, size, outsize) \
    fprintf(stderr, "-ERROR 参数超出命令 %s 固定长度：%zu, 参数长度：%zu\n", (cmd), (size), (outsize))

/* 设置string值 */
#define VMARCH_SET_CHR(opt, arg, asize, val)                                        \
    if ((asize) > 0) {                                                              \
        if ((asize) <= sizeof((val))) {                                             \
            strcpy((val), (arg));                                                   \
        } else {                                                                    \
            VMARCH_ERROR_OUT_OF_INDEX(opt, sizeof((val)), (asize));                 \
            exit(-1);                                                               \
        }                                                                           \
    }

/* 设置bool值 */
#define VMARCH_SET_BOOL(val) ( val = TRUE )

VMARCHCMD has_cmd(char **argv)
{
    char *ch_cmd = argv[1];

    if (ch_cmd == NULL)
        goto NO_CMD;

    if (strcmp(ch_cmd, "start") == 0) return VMARCHCMD_START;
    if (strcmp(ch_cmd, "stop") == 0) return VMARCHCMD_STOP;
    if (strcmp(ch_cmd, "restart") == 0) return VMARCHCMD_RESTART;
    if (strcmp(ch_cmd, "ps") == 0) return VMARCHCMD_PS;
    if (strcmp(ch_cmd, "exec") == 0) return VMARCHCMD_EXEC;
    if (strcmp(ch_cmd, "pak") == 0) return VMARCHCMD_PAK;
    if (strcmp(ch_cmd, "dump") == 0) return VMARCHCMD_DUMP;
    if (strcmp(ch_cmd, "version") == 0) return VMARCHCMD_VERSION;

NO_CMD:
    return VMARCHCMD_NULL;
}

void vmarch_make_cmdline(int argc, char **argv, struct vmarch_option_flags *flags)
{
    int         opt;
    VMARCHCMD   cmd;

    cmd = has_cmd(argv);
    flags->cmd |= cmd;

    while (getopts(argc, argv, VMARCH_OPTIONS, ARRAY_SIZE(VMARCH_OPTIONS), &opt) != -1) {
        size_t argsize = xoptarg != NULL ? strlen(xoptarg) : 0;

        switch (opt) {
            case OPT_NSD: VMARCH_SET_CHR(xoptopt, xoptarg, argsize, flags->nsd); break;
            case OPT_CP: VMARCH_SET_CHR(xoptopt, xoptarg, argsize, flags->cp); break;
            case OPT_PORT: VMARCH_SET_CHR(xoptopt, xoptarg, argsize, flags->port); break;
            case OPT_DEBUG_PORT: VMARCH_SET_CHR(xoptopt, xoptarg, argsize, flags->dp); break;
            case OPT_XTAIL: VMARCH_SET_BOOL(flags->xtl); break;
            case OPT_MONITOR: VMARCH_SET_BOOL(flags->mon); break;
            case OPT_VERSION: VMARCH_SET_BOOL(flags->v); break;
        }
    }
}