/* AUTHOR: TIAN_SHENG, DATE: 2022/7/20 */
#include <iostream>
#include <unistd.h>
#include "verror.h"
#include <cstring>

/**
 * 执行Cmd命令并打印缓冲区
 * @param __Cmd shell 或 bat命令
 */
void pcmdexec(const char *__Cmd)
{
    FILE *p_popen = popen(__Cmd, "r");
    if (!p_popen)
        verror("open proc failed! __Cmd: %s\n", __Cmd);

    char tmp[1024];
    while (fgets(tmp, sizeof(tmp), p_popen) != NULL)
        printf("%s", tmp);

    pclose(p_popen);
}

/**
 * 执行Cmd命令将缓冲区输出到一个 char *buf 中，然后返回出去。
 * @param __Cmd shell 或 bat命令
 */
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

/**
 * 释放掉 rcmdexec 函数返回的缓冲区
 * @param __Buf 缓冲区指针
 */
void rcmdexec_free_buffer(char *__Buf)
{
    free(__Buf);
}