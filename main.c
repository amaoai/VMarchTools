/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include <stdio.h>
#include "init.h"

int main(int argc, char **argv)
{
    struct vmarch_option_flags flags;
    vmarch_init_option_flags(&flags);

    if (!vmarch_make_cmdline(argc, argv, &flags)) {
        // error
    }

    return 0;
}
