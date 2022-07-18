/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#include "cmdexec.h"

#include <string.h>

int rcmdexec(const char *__Cmd, char *__Buf, size_t __BufSiz)
{
    FILE *fp;
    char tmpbuf[1024];

    if ((fp = popen(__Cmd, "r")) != NULL) {
        while (fgets(tmpbuf, sizeof(tmpbuf), fp) != NULL) {
            strcat(__Buf, tmpbuf);
        }

        pclose(fp);

        return 0;
    }

    return -1;
}

int pcmdexec(const char *__Cmd)
{
    FILE *fp;
    char tmpbuf[1024];

    if ((fp = popen(__Cmd, "r")) != NULL) {
        while (fgets(tmpbuf, sizeof(tmpbuf), fp) != NULL)
            printf("%s", tmpbuf);

        pclose(fp);

        return 0;
    }

    return -1;
}