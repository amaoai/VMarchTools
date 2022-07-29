/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCH_CMDEXEC_H
#define VMARCH_CMDEXEC_H

#include <string>

/* 是否打印执行的命令行 */
#define ENABLE_PRINT_COMMAND false

void pcmdexec(const std::string &cmd, bool is_print_cmd = ENABLE_PRINT_COMMAND);
void rcmdexec(const std::string &cmd, std::string *buf, bool is_print_cmd = ENABLE_PRINT_COMMAND);

#endif /* VMARCH_CMDEXEC_H */
