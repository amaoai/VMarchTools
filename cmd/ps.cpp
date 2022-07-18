/* AUTHOR: TIAN_SHENG, DATE: 2022/7/15 */
#include "vmarchcmd.h"

#include "cmdexec.h"
#include "color.h"
#include <sstream>
#include <unordered_map>

#define PID_SPACE_SIZE 10

// 查找 Java 进程
// =============
void find_java_proc(std::unordered_map<std::string, std::string> *procmap)
{
    char cmdbuf[0xFFFF];
    rcmdexec("jps -l", cmdbuf, sizeof(cmdbuf));

    std::stringstream buf_stream(cmdbuf);
    std::string line;

    while (getline(buf_stream, line)) {
        size_t pos = line.find(" ");
        std::string pid = line.substr(0, pos);
        std::string name = line.substr(pos + 1, line.size());
        procmap->insert(std::pair<std::string, std::string>(name, pid));
    }
}

// cmdexec: (ps)
// ================
void vmarchcmd_exec_ps(const struct vmarch_option_flags *p_optflags)
{
    std::unordered_map<std::string, std::string> procmap; /* K=name, V=pid */
    find_java_proc(&procmap);

    for (auto &entry : procmap) {
        std::string pid = entry.second.c_str();
        size_t pidsize = pid.size();

        /* 补齐空格，排列的工整一点 */
        if (pidsize < PID_SPACE_SIZE) {
            size_t fillin = PID_SPACE_SIZE - pidsize;
            for (int i = 0; i < fillin; i++)
                pid.insert(0, " ");
        }

        printf("PID[%s%s%s] - %s\n",
               VMARCH_COLOR_GREEN,
               pid.c_str(),
               VMARCH_COLOR_RESET,
               entry.first.c_str());
    }

}