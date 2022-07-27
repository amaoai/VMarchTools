/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#include "vmarchcmd.h"
#include "cmdexec.h"
#include "vmarchtools.h"

void cmd_vps(const std::string *pcmd)
{

    pcmdexec(vmarchtools::fmt("ps -ef | grep %s | grep -v grep | grep -v vmarch",
                              pcmd->empty() ? "java" : pcmd->c_str()));
}