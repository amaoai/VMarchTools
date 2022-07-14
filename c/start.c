#include "vmarchcmd.h"

// cmdexec: (start)
// ================
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags)
{
    printf("exec: -start\n");

    DIR *dir;
    struct dirent *ent;

    char curwd[_MAX_FILE_NAME];
    getcwd(curwd, sizeof(curwd));

    if ((dir = opendir(curwd)) == NULL) {
        fprintf(stderr, "-ERROR 打开工作目录%s失败。请检查目录是否存在", curwd);
        exit(-1);
    }

    char *p_ch;
    char jarpack[_MAX_FILE_NAME] = {};

    while ((ent = readdir(dir)) != NULL) {
        p_ch = strrchr(ent->d_name, '.');

        /* 查找后缀为 .jar 并且文件类型不是目录的文件名 */
        if ((p_ch != NULL && strcmp(p_ch, ".jar") == 0) && ent->d_type != DT_DIR) {
            if (strlen(jarpack) > 0)
                _VMARCH_THROW_ERROR("-ERROR 当前目录下存在多个 JAR 文件。");

            strcpy(jarpack, ent->d_name);
        }
    }

    closedir(dir);
}