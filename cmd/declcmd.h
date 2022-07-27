/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_DECLCMD_H
#define VMARCH_DECLCMD_H

#include "vmarchcmd.h"
#include <string>

extern void cmd_start(const std::string *pcmd, const struct vmarchcmd_flags *flags);
extern void cmd_stop(const std::string *pcmd);
extern void cmd_vps(const std::string *pcmd);

#endif /* VMARCH_DECLCMD_H */
