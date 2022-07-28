/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCHTOOLS_STATUS_H
#define VMARCHTOOLS_STATUS_H

#include <string>
#include <vector>

struct proc_port_info {
    std::string protocol;
    std::string port;
};

struct system_proc_info {
    std::string pid;
    std::string user;
    std::string name;
    std::string cmd;
    std::string status;
    std::string start;
    std::string time;
    std::string tty;
    float cpu;
    float mem;
    float vsz;
    float rss;
    std::vector<struct proc_port_info> prots;
};

std::string getpid(const std::string *pcmd);
/* 获取进程状态 */
void getproc(const std::string &pid, struct system_proc_info *ptr);
/* 打印进程状态 */
void print_proc_info(const struct system_proc_info *proc);

#endif /* VMARCHTOOLS_STATUS_H */
