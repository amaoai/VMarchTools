/* AUTHOR: TIAN_SHENG, DATE: 2022/7/20 */
#include <iostream>
#include <unistd.h>
#include "verror.h"
#include <cstring>

#define PCMD(cmd) printf("[CMD] - %s\n", cmd)

void pcmdexec(const char *__Cmd)
{
    FILE *p_popen = popen(__Cmd, "r");
    if (!p_popen)
        verror("open proc failed! __Cmd: %s\n", __Cmd);

    PCMD(__Cmd);

    char tmp[1024];
    while (fgets(tmp, sizeof(tmp), p_popen) != NULL)
        printf("%s", tmp);

    pclose(p_popen);
}

char *rcmdexec(const char *__Cmd)
{
    char  *p_buf;
    size_t buflen;
    size_t bufsize;

    buflen = 0;
    bufsize = 1024;
    p_buf = (char*) malloc(bufsize);

    FILE *p_popen = popen(__Cmd, "r");
    if (!p_popen)
        verror("open proc failed! __Cmd: %s\n", __Cmd);

    PCMD(__Cmd);

    char tmp[1024];
    while (fgets(tmp, sizeof(tmp), p_popen) != NULL) {
        size_t tmplen = strlen(tmp);
        if ((bufsize - buflen) > tmplen) {
            strcat(p_buf, tmp);
            buflen += tmplen;
        } else {
            bufsize = bufsize + tmplen * 2;
            p_buf = (char *) realloc(p_buf, bufsize);
        }
    }

    pclose(p_popen);

    return p_buf;
}

void rcmdexec_free_buffer(char *__Buf)
{
    free(__Buf);
}