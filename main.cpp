/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include "vmarchcmd.h"

int main(int argc, char **argv)
{
    struct vmarch_option_flags optflags = {};

    /* 初始化命令行 */
    vmarch_make_cmdline(argc, argv, &optflags);

#ifndef NDEBUG
    vmarch_option_flags_printf((&optflags));
#endif

    /* 执行命令 */
    vmarchcmd_exec(&optflags);

    return 0;
}
