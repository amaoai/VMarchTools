/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "declcmd.h"
#include "status.h"
#include "vps.h"
#include "cmdexec.h"

unsigned long getpid(const std::string *pcmd)
{
    if (vmarchtools::is_number(*pcmd))
        return vmarchtools::value_of<unsigned long>(*pcmd);

    std::string javafile = check_java_file(pcmd);

    unsigned long pid;
    getvps_pid(javafile, &pid);

    return pid;
}

#define getps_aux_element(pid, num, ptr) \
    rcmdexec(getps(std::to_string(pid), "printf \"%s\", "#num), (ptr))

void getproc(unsigned long pid, struct system_proc_info *ptr)
{
    std::string buf;

    ptr->pid = pid;
    if (!getvps_name(pid, &ptr->name))
        vmarchtools::verror("进程不存在，或当前进程非Java进程", pid);

    getvps_cmd(pid, &ptr->cmd);

    /* ps aux | grep xxx 使用 awk 根据对应的列获取数据 */
    getps_aux_element(pid, $1, &ptr->user);
    getps_aux_element(pid, $7, &ptr->tty);
    getps_aux_element(pid, $9, &ptr->start_time);
    getps_aux_element(pid, $10, &ptr->running_time);

    getps_aux_element(pid, $3, &buf);
    ptr->cpu = vmarchtools::value_of<float>(buf);
    getps_aux_element(pid, $4, &buf);
    ptr->mem = vmarchtools::value_of<float>(buf);
    getps_aux_element(pid, $5, &buf);
    ptr->vsz = vmarchtools::value_of<unsigned long>(buf);
    getps_aux_element(pid, $6, &buf);
    ptr->rss = vmarchtools::value_of<unsigned long>(buf);

    /* 查看 /proc/<pid>/status 文件获取数据 */
    rcmdexec(vmarchtools::fmt("cat /proc/%d/status | grep State | awk '{print $2}'", pid), &ptr->state);
    rcmdexec(vmarchtools::fmt("cat /proc/%d/status | grep State | awk '{print $3}'", pid), &ptr->state_explain);

    /* 获取当前进程线程数 */
    rcmdexec(vmarchtools::fmt("cat /proc/%d/status | grep Threads | awk '{print $2}'", pid), &buf);
    ptr->threads = vmarchtools::value_of<unsigned int>(buf);

    /* 获取jar包所在位置 */
    std::string location_buf;
    rcmdexec(vmarchtools::fmt("echo \"$(cd /proc/3945702/cwd & pwd -LP)\"", pid), &location_buf);
    ptr->location = location_buf;
}

void print_proc_info(const struct system_proc_info *proc)
{
    printf("%s●%s Java Process Status - VMarchTools <status> command.\n", VMARCH_COLOR_BOLD_GREEN, VMARCH_COLOR_RESET);
    printf("    Jar: %s\n", proc->name.c_str());
    printf("    Location: %s\n", proc->location.c_str());
    printf("    Main PID: %s%lu%s\n", VMARCH_COLOR_BOLD_BLUE, proc->pid, VMARCH_COLOR_RESET);
    printf("      └─CPU: %.2f%\n", proc->cpu);
    printf("      └─Memory: %.2f%\n", proc->mem);
    printf("      └─VSZ(kb): %lu\n", proc->vsz);
    printf("      └─RSS(kb): %lu\n", proc->rss);
    printf("    Threads: %u\n", proc->threads);
    printf("    Main State: %s%s %s%s\n", VMARCH_COLOR_BOLD_GREEN, proc->state.c_str(), proc->state_explain.c_str(), VMARCH_COLOR_RESET);
    printf("    Terminal: %s\n", proc->tty.c_str());
    printf("  Start & Run time:  %s/%s\n", proc->start_time.c_str(), proc->running_time.c_str());
    printf("  Cmdline: %s\n", proc->cmd.c_str());
}

void cmd_status(const std::string *pcmd, const struct vmarchcmd_flags *flags, VMARCHFLAGS)
{
    unsigned long pid = getpid(pcmd);

    if (!flags->detail.empty()) {
        pcmdexec(vmarchtools::fmt("cat /proc/%lu%s", pid, flags->detail.c_str()));
    } else {
        struct system_proc_info proc {};
        getproc(pid, &proc);
        print_proc_info(&proc);
    }

    if (flags->threads) {
        printf("\n");
        pcmdexec(vmarchtools::fmt("jstack -l %lu", pid));
    }

    if (flags->network) {
        printf("\n");
        pcmdexec(vmarchtools::fmt("netstat -anp | grep %lu | grep -v unix", pid));
    }
}