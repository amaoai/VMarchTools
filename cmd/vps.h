/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCH_VPS_H
#define VMARCH_VPS_H

#include <string>

void getvps_cmd(unsigned long pid, std::string *p_buf);
bool getvps_name(unsigned long pid, std::string *p_buf);
bool getvps_pid(const std::string &name, unsigned long *p_pid);

#endif /* VMARCH_VPS_H */
