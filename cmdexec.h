/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCH_CMDEXEC_H
#define VMARCH_CMDEXEC_H

#include <string>

void pcmdexec(const std::string &cmd, bool is_print_cmd = false);
void rcmdexec(const std::string &cmd, std::string *buf, bool is_print_cmd = false);

#endif /* VMARCH_CMDEXEC_H */
