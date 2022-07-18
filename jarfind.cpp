/* AUTHOR: TIAN_SHENG, DATE: 2022/7/18 */
#include "jarfind.h"

#include <iostream>
#include <stdexcept>
#include <unistd.h>

/* 遍历当前工作空间 */
std::string vmarch_getcwd_jarfile()
{
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> cwdfvec;

    char curwd[_MAX_FILE_NAME];
    getcwd(curwd, sizeof ( curwd ));

    if ((dir = opendir(curwd)) == NULL) {
        fprintf(stderr, "-ERROR 打开工作目录%s失败。请检查目录是否存在", curwd);
        exit(-1);
    }

    while ((ent = readdir(dir)) != NULL)
        if (!_IGNORE_DIR(ent->d_name))
            cwdfvec.push_back(ent->d_name);

    closedir(dir);

    // 查找 .jar 结尾的文件名
    std::vector<std::string> jarpacks;
    for (std::string &name : cwdfvec) {
        if (has_suffix(name, "jar"))
            jarpacks.push_back(name);
    }

    if (jarpacks.empty())
        throw std::runtime_error("没有查找到当前目录下的可运行JAR");

    std::string service = jarpacks[0];

    if (jarpacks.size() > 1) {
        printf("存在多个 JAR 文件，请根据序号选择要启动的服务: \n");

        int i = 0;
        for (auto &jarpack : jarpacks) {
            printf("  [%d] %s\n", i, jarpack.c_str());
            ++i;
        }

        printf("请输入服务序号: ");
        unsigned seqnum;
        std::cin >> seqnum;
        service = jarpacks[seqnum];
    }

    return std::string(service);
}