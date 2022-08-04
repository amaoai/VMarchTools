/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCHTOOLS_STATUS_H
#define VMARCHTOOLS_STATUS_H

#include <string>
#include <vector>
#include "vmarchtools.h"

struct proc_port_info {
    std::string protocol;
    std::string port;
};

struct system_proc_info {
    unsigned long pid;
    std::string user;
    std::string name;
    std::string cmd;
    std::string state;
    std::string state_explain;
    std::string start_time;
    std::string running_time;
    std::string tty;
    std::string location;
    float cpu;
    float mem;
    unsigned long vsz;
    unsigned long rss;
    unsigned int threads;
    std::vector<struct proc_port_info> prots;
};

unsigned long getpid(const std::string *pcmd);
void getproc(unsigned long pid, struct system_proc_info *ptr); /* 获取进程状态 */
void print_proc_info(const struct system_proc_info *proc); /* 打印进程状态 */
extern void get_jvm_threads(unsigned long pid, std::vector<struct jvm_thread_info> *ptr);

#endif /* VMARCHTOOLS_STATUS_H */
