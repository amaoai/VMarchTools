/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_DECLCMD_H
#define VMARCH_DECLCMD_H

#include "vmarchcmd.h"
#include "vmarchtools.h"
#include <string>

inline static std::string getps(const std::string &grep)
{
    return vmarchtools::fmt(
            R"(ps aux | grep %s | grep -v grep | grep -v VMarchTools | grep -v vmarch)", grep.c_str());
}

inline static std::string getps(const std::string &grep, const std::string &awk_cmd)
{
    return vmarchtools::fmt(
            R"(ps aux | grep %s | grep -v grep | grep -v VMarchTools | grep -v vmarch | awk '{ %s }')",
            grep.c_str(), awk_cmd.c_str());
}


extern void cmd_start(const std::string *pcmd, const struct vmarchcmd_flags *flags, VMARCHFLAGS);
extern void cmd_stop(const std::string *pcmd, VMARCHFLAGS);
extern void cmd_vps(const std::string *pcmd, VMARCHFLAGS);
extern void cmd_status(const std::string *pcmd, VMARCHFLAGS);

#endif /* VMARCH_DECLCMD_H */
