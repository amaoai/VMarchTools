/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#include "cmdexec.h"

#include <malloc.h>
#include <string.h>

char *_buf;

int __fcmdexec(const char *cmd, __func_read_buf __FuncReadBuf)
{
    FILE *fp;
    char tmpbuf[2048];

    static unsigned seq = -1;
    printf("[%d] - %s\n", (++seq), cmd);

    if ((fp = popen(cmd, "r")) != NULL) {
        while (fgets(tmpbuf, sizeof(tmpbuf), fp) != NULL)
            __FuncReadBuf(tmpbuf);

        pclose(fp);

        return 0;
    }

    return -1;
}

void __read_buf(const char *rbuf)
{
    strcat(_buf, rbuf);
}

void rcmdexec(const char *__Cmd, char *__Buf, size_t __BufSiz)
{
    _buf = (char *) malloc(__BufSiz);
    __fcmdexec(__Cmd, __read_buf);
    strcpy(__Buf, _buf);
    free(_buf);
    _buf = NULL;
}