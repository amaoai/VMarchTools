/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "cmdexec.h"
#include <stdexcept>

void system_command_exec(const std::string &cmd, void *ptr, f_system_command_exec_callback f_callback)
{
    FILE *fp;

    if ((fp = popen(cmd.c_str(), "r")) == nullptr)
        throw std::runtime_error("popen failed");

    printf("[CMD] - %s\n", cmd.c_str());

    /* 读取buf */
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) != nullptr)
        f_callback(buf, ptr);

    pclose(fp);
}

void pcmdexec(const std::string &cmd)
{
    system_command_exec(cmd, nullptr, [](const char *buf, void *) -> void {
        printf("%s", buf);
    });
}

void rcmdexec(const std::string &cmd, std::string *buf)
{
    system_command_exec(cmd, buf, [](const char *buf, void *p_buf) -> void {
        ((std::string *) p_buf)->append(buf);
    });
}