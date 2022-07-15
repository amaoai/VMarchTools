#include "vmarchcmd.h"

#include <vector>
#include <string>
#include <unistd.h>

/* 遍历当前工作空间 */
void iter_getcwd_files(std::vector<std::string> *cwdfvec)
{
    DIR *dir;
    struct dirent *ent;

    char curwd[_MAX_FILE_NAME];
    getcwd(curwd, sizeof ( curwd ));

    if ((dir = opendir(curwd)) == NULL) {
        fprintf(stderr, "-ERROR 打开工作目录%s失败。请检查目录是否存在", curwd);
        exit(-1);
    }

    while ((ent = readdir(dir)) != NULL)
        if (!_IGNORE_DIR(ent->d_name))
            cwdfvec->push_back(ent->d_name);

    closedir(dir);
}

// cmdexec: (start)
// ================
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags)
{
    printf("exec: -start\n");

    std::vector<std::string> cwdfvec;       /* 当前工作目录下的所有文件名 */
    iter_getcwd_files(&cwdfvec);

    // 查找 .jar 结尾的文件名
    std::vector<std::string> jarpacks;
    for (std::string &name : cwdfvec) {

    }
}