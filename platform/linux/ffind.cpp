/* AUTHOR: TIAN_SHENG, DATE: 2022/7/20 */
#include "cmdexec.h"
#include "vmarchio.h"
#include "verror.h"
#include <sstream>
#include <string.h>
#include <unistd.h>

#define MAX_CMD (PATH_MAX)

void getpwd(char *__Buf, size_t __Size)
{
    getcwd(__Buf, __Size);
}

void find(const char *__Path, const char *__Cond, std::vector<std::string> *__OutVec)
{
    char __Cmd[MAX_CMD] = {};
    snprintf(__Cmd, sizeof(__Cmd), "find %s %s", __Path, __Cond);

    char *buf = rcmdexec(__Cmd);
    std::stringstream stream(buf);
    rcmdexec_free_buffer(buf);

    std::string line;
    while (getline(stream, line))
        __OutVec->push_back(line);
}

void getexedir(char *__Buf)
{
    char __Cmd[MAX_CMD] = "readlink -f $0";
    char *buf = rcmdexec(__Cmd);
    getparent(buf, __Buf);
    rcmdexec_free_buffer(buf);
}

void getparent(const char *__Path, char *__Buf)
{
    const char *p_ch = strrchr(__Path, '/');

    if (p_ch == NULL)
        return;

    strncpy(__Buf, __Path, p_ch - __Path);
    __Buf[p_ch - __Path] = '\0';
}