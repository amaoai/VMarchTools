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

void getexedir(char *__Buf, size_t __Size)
{
    char path[PATH_MAX];
    readlink("/proc/self/exe", path, sizeof(path));
    getparent(path, __Buf, __Size);
}

void getparent(const char *__Path, char *__Buf, size_t __Size)
{
    const char *p_ch = strrchr(__Path, '/');

    /* 缓冲区大小检查 */
    if (__Size < (p_ch - __Path + 1))
        verror("buffer size is too small");

    strncpy(__Buf, __Path, p_ch - __Path);
    __Buf[p_ch - __Path] = '\0';
}