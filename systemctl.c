/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#include "systemctl.h"

#include <stdio.h>

int systemctl_exec_cmd(const char *cmd)
{
    FILE *fp;
    char bufsize[2048];

    printf("run cmd: %s\n", cmd);

    if ((fp = popen(cmd, "r")) != NULL) {
        while (fgets(bufsize, sizeof(bufsize), fp) != NULL)
            printf("%s", bufsize);

        pclose(fp);

        return 0;
    }

    return -1;
}
