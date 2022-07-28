/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "declcmd.h"
#include "status.h"
#include "vps.h"
#include "vmarchtools.h"
#include "cmdexec.h"

std::string getpid(const std::string *pcmd)
{
    if (vmarchtools::is_number(*pcmd))
        return *pcmd;

    std::string javafile = check_java_file(pcmd);

    std::string pid;
    getvps_pid(javafile, &pid);

    return pid;
}

#define getelem(pid, num, ptr) \
    rcmdexec(vmarchtools::fmt("ps aux | grep %s | grep -v grep | awk '{printf \"%%s\", %s}'", pid.c_str(), num), (ptr))


void getproc(const std::string &pid, struct system_proc_info *ptr)
{
    std::string buf;

    ptr->pid.assign(pid);
    if (!getvps_name(pid, &ptr->name))
        vmarchtools::verror("进程不存在或有多个，要不就是已经被杀了");

    getelem(pid, "$1", &ptr->user);
    getelem(pid, "$7", &ptr->tty);
    getelem(pid, "$8", &ptr->status);
    getelem(pid, "$9", &ptr->start);
    getelem(pid, "$10", &ptr->time);

    getelem(pid, "$3", &buf);
    ptr->cpu = atof(buf.c_str());
    getelem(pid, "$4", &buf);
    ptr->mem = atof(buf.c_str());
    getelem(pid, "$5", &buf);
    ptr->vsz = atof(buf.c_str());
    getelem(pid, "$6", &buf);
    ptr->rss = atof(buf.c_str());
}

void print_proc_info(const struct system_proc_info *proc)
{
    vmarchtools::printf_to_stdout("%s•%s %s - VMarchTools proc status\n", VMARCH_COLOR_BOLD_GREEN, VMARCH_COLOR_RESET, proc->name.c_str());
    vmarchtools::printf_to_stdout("    CPU: %.2f%, Memory: %.2f%\n", proc->cpu, proc->mem);
    vmarchtools::printf_to_stdout("    VSZ: %.2f%, RSS: %.2f%\n", proc->vsz, proc->rss);
    vmarchtools::printf_to_stdout("  Active Status: %s%s%s\n", VMARCH_COLOR_BOLD_GREEN, proc->status.c_str(), VMARCH_COLOR_RESET);
    vmarchtools::printf_to_stdout("  tty: %s\n", proc->tty.c_str());
    vmarchtools::printf_to_stdout("Start, Time %s/%s\n", proc->start.c_str(), proc->time.c_str());
}

void cmd_status(const std::string *pcmd, VMARCHFLAGS)
{
    std::string pid = getpid(pcmd);
    struct system_proc_info proc {};
    getproc(pid, &proc);
    print_proc_info(&proc);
}