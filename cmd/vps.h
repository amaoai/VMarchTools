/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#ifndef VMARCH_VPS_H
#define VMARCH_VPS_H

#include <string>

bool getvps_cmd(const std::string &pid, std::string *p_buf);
bool getvps_name(const std::string &pid, std::string *p_buf);
bool getvps_pid(const std::string &name, std::string *p_buf);

#endif /* VMARCH_VPS_H */
