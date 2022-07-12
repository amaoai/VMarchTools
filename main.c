/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include <stdio.h>
#include "init.h"

int main(int argc, char **argv)
{
    struct vmarch_option_flags flag;

    if (!vmarch_make_cmdline(argc, argv, &flag)) {
        // error
    }

    return 0;
}
