/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "cmdexec.h"
#include <stdexcept>

typedef void(*f_system_command_exec_callback)(const char *buf, void *);

void __system_command_exec(const std::string &cmd, bool is_print, void *ptr, f_system_command_exec_callback f_callback)
{
    FILE *fp;

    if (is_print)
        printf("[CMD] - %s\n", cmd.c_str());

    if ((fp = popen(cmd.c_str(), "r")) == nullptr)
        throw std::runtime_error("popen failed");

    /* 读取buf */
    char buf[1024] = {};
    while (!feof(fp)) {
        if (fgets(buf, sizeof(buf), fp) != nullptr)
            f_callback(buf, ptr);
    }

    pclose(fp);
}

void pcmdexec(const std::string &cmd, bool is_print)
{
    __system_command_exec(cmd, is_print, nullptr, [](const char *buf, void *) -> void {
        printf("%s", buf);
    });
}

void rcmdexec(const std::string &cmd, std::string *buf, bool is_print)
{
    __system_command_exec(cmd, is_print, buf, [](const char *buf, void *p_buf) -> void {
        ((std::string *) p_buf)->append(buf);
    });
}