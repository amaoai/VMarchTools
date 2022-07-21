/* AUTHOR: TIAN_SHENG, DATE: 2022/7/20 */
#include "vmarchcmd.h"
#include "vmarchio.h"
#include <string>

// cmdexec: (dump)
// ================
void vmarch_cmd_exec_dump(std::string &pcmd)
{
    const char *dump_file_name = pcmd.empty() ? "javadump" : pcmd.c_str();

    char xcmd[1024];
    snprintf(xcmd, sizeof(xcmd), "jmap -dump:file=%s.hprof,format=b %s", dump_file_name, "0");

    pcmdexec(xcmd);
}