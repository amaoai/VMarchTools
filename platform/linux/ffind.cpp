/* AUTHOR: TIAN_SHENG, DATE: 2022/7/20 */
#include "cmdexec.h"
#include "vmarchio.h"
#include <sstream>
#include <unistd.h>

#define MAX_CMD (PATH_MAX + 16)

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