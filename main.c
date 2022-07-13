/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include <stdio.h>
#include "vmarchcmd.h"

void vmarch_submit_cmd(struct vmarch_option_flags *optflag)
{
    if (optflag->cmd == VMARCHCMD_START) {

    }
}

int main(int argc, char **argv)
{
    struct vmarch_option_flags optflag;
    vmarch_init_option_flags(&optflag);

    /* 初始化命令行 */
    vmarch_make_cmdline(argc, argv, &optflag);

#ifdef vmarch_enable_debug
    vmarch_option_flags_printf(optflag);
#endif

    /* 执行命令 */
    vmarch_submit_cmd(&optflag);

    return 0;
}
