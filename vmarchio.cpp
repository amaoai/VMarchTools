/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "vmarchio.h"
#include <dirent.h>
#include <unistd.h>

std::string getpcwd()
{
    char buf[PATH_MAX];
    getcwd(buf, sizeof(buf));
    return buf;
}

std::vector<std::string> find_file(const std::string &path, const std::string &pattern)
{
    std::vector<std::string> ffiles;

    DIR *dir = opendir(path.c_str());
    if (dir == nullptr)
        return ffiles;

    struct dirent *ent = nullptr;
    while ((ent = readdir(dir)) != nullptr) {
        std::string file_name = ent->d_name;
        if (file_name.find(pattern) != std::string::npos)
            ffiles.push_back(file_name);
    }

    closedir(dir);

    return ffiles;
}

std::string getparent(const std::string &path)
{
    std::string parent_path = path;
    size_t pos = parent_path.find_last_of('/');
    if (pos != std::string::npos)
        parent_path = parent_path.substr(0, pos);
    return parent_path;
}