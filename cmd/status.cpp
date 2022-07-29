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


#define getps_aux_elem(pid, num, ptr) \
    rcmdexec(getps(pid, "printf \"%s\", "#num), (ptr))

void getproc(const std::string &pid, struct system_proc_info *ptr)
{
    std::string buf;

    ptr->pid.assign(pid);
    if (!getvps_name(pid, &ptr->name))
        vmarchtools::verror("进程不存在或有多个（如果PID很长就是多个PID组合起来的），PID=%s", pid.c_str());

    getvps_cmd(pid, &ptr->cmd);

    /* ps aux | grep xxx 使用 awk 根据对应的列获取数据 */
    getps_aux_elem(pid, $1, &ptr->user);
    getps_aux_elem(pid, $7, &ptr->tty);
    getps_aux_elem(pid, $9, &ptr->start_time);
    getps_aux_elem(pid, $10, &ptr->running_time);

    getps_aux_elem(pid, $3, &buf);
    ptr->cpu = vmarchtools::value_of<float>(buf);
    getps_aux_elem(pid, $4, &buf);
    ptr->mem = vmarchtools::value_of<float>(buf);
    getps_aux_elem(pid, $5, &buf);
    ptr->vsz = vmarchtools::value_of<float>(buf);
    getps_aux_elem(pid, $6, &buf);
    ptr->rss = vmarchtools::value_of<float>(buf);

    /* 查看 /proc/<pid>/status 文件获取数据 */
    rcmdexec(vmarchtools::fmt("cat /proc/%s/status | grep State | awk '{print $2}'", pid.c_str()), &ptr->state);
    rcmdexec(vmarchtools::fmt("cat /proc/%s/status | grep State | awk '{print $3}'", pid.c_str()), &ptr->state_explain);

}

void print_proc_info(const struct system_proc_info *proc)
{
    vmarchtools::printf_to_stdout("%s•%s %s from VMarchTools <status> command.\n", VMARCH_COLOR_BOLD_GREEN, VMARCH_COLOR_RESET, proc->name.c_str());
    vmarchtools::printf_to_stdout("    Start/Run Status (%s)\n", proc->cmd.c_str());
    vmarchtools::printf_to_stdout("      └─CPU: %.2f%\n", proc->cpu);
    vmarchtools::printf_to_stdout("      └─Memory: %.2f%\n", proc->mem);
    vmarchtools::printf_to_stdout("      └─VSZ: %.2f%\n", proc->vsz);
    vmarchtools::printf_to_stdout("      └─RSS: %.2f%\n", proc->rss);
    vmarchtools::printf_to_stdout("    Main PID: %s\n", proc->pid.c_str());
    vmarchtools::printf_to_stdout("  Main State: %s%s %s%s\n", VMARCH_COLOR_BOLD_GREEN, proc->state.c_str(), proc->state_explain.c_str(), VMARCH_COLOR_RESET);
    vmarchtools::printf_to_stdout("  Terminal status: %s\n", proc->tty.c_str());
    vmarchtools::printf_to_stdout("Start & Run time:  %s/%s\n", proc->start_time.c_str(), proc->running_time.c_str());
}

void cmd_status(const std::string *pcmd, VMARCHFLAGS)
{
    std::string pid = getpid(pcmd);
    struct system_proc_info proc {};
    getproc(pid, &proc);
    print_proc_info(&proc);
}