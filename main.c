/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include <stdio.h>
#include "init.h"
#include "cmd/start/startcmd.h"

void vmarch_exec_cmd(struct vmarch_option_flags *flags)
{

}

int main(int argc, char **argv)
{
    struct vmarch_option_flags flags;
    vmarch_init_option_flags(&flags);

    /* 初始化命令行 */
    vmarch_make_cmdline(argc, argv, &flags);

#ifdef vmarch_enable_debug
    vmarch_option_flags_printf(flags);
#endif

    /* 执行命令 */
    vmarch_exec_cmd(&flags);

    return 0;
}
