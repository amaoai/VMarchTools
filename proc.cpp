/* AUTHOR: TIAN_SHENG, DATE: 2022/7/25 */
#include "proc.h"

char *source_director_init();
char *__CURENT_SOURCE_DIRECTOR__ = source_director_init();

char *source_director_init()
{
    char *p_source_director = (char *) malloc(PATH_MAX);

    char path[PATH_MAX];
    getexedir(path, sizeof(path));
    getparent(path, p_source_director, PATH_MAX);

    return p_source_director;
}

void proc_exec(const std::string &__ProcName, const std::string __Pcmd, std::string &__Pval)
{
    char cmd[PATH_MAX];
    snprintf(cmd, sizeof(cmd), "bash %s/sh/xps %s", __CURENT_SOURCE_DIRECTOR__, __Pcmd.c_str());

    char *buf = rcmdexec(cmd);
    __Pval.append(buf);
    rcmdexec_free_buffer(buf);
}