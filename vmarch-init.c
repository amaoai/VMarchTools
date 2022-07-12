/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include "init.h"
#include <string.h>
#include <stdio.h>

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
    if (strcmp(ch_cmd, "pack") == 0) return VMARCHCMD_PACK;
    if (strcmp(ch_cmd, "dump") == 0) return VMARCHCMD_DUMP;

NO_CMD:
    return VMARCHCMD_NULL;
}

int vmarch_make_cmdline(int argc, char **argv, struct vmarch_option_flags *flags)
{
    int         opt;
    VMARCHCMD   cmd;

    if ((cmd = has_cmd(argv)) != VMARCHCMD_NULL)
        printf("CMD: %d\n", cmd);

    while (getopts(argc, argv, VMARCH_OPTIONS, ARRAY_SIZE(VMARCH_OPTIONS), &opt) != -1) {
        switch (opt) {
            case OPT_NSD: printf("--notice-shutdown %s\n", optarg); break;
            case OPT_PORT: printf("-port %s\n", optarg); break;
            case OPT_DEBUG_PORT: printf("--debug-port %s\n", optarg); break;
            case OPT_MONITOR: printf("--monitor %s\n", optarg); break;
        }
    }

    return TRUE;
}