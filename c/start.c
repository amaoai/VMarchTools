#include "vmarchcmd.h"
#include "vmarchio.h"

// cmdexec: (start)
// ================
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags)
{
    printf("exec: -start\n");

    DIR           *dir;
    struct dirent *ent;

    char curwd[_MAX_FILE_NAME];
    getcwd(curwd, sizeof(curwd));

    if ((dir = opendir(curwd)) == NULL) {
        fprintf(stderr, "-ERROR 打开工作目录%s失败。请检查目录是否存在", curwd);
        exit(-1);
    }

    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }

    closedir(dir);
}