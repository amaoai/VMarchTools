/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCH_CMDEXEC_H
#define VMARCH_CMDEXEC_H

#include <string>

typedef void(*f_system_command_exec_callback)(const char *buf, void *);
void system_command_exec(const std::string &cmd, void *, f_system_command_exec_callback);
void pcmdexec(const std::string &cmd);
void rcmdexec(const std::string &cmd, std::string *buf);

#endif /* VMARCH_CMDEXEC_H */