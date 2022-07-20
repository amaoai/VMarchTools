/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#ifndef VMARCH_VMARCHCMD_H
#define VMARCH_VMARCHCMD_H

#include "typedef.h"
#include "verror.h"
#include "cmdexec.h"
#include <string>

struct vmarch_start_flags {
    bool        xtl;
    std::string vdb;
    std::string cp;
};

void vmarch_cmd_main(int, char **);

#endif /* VMARCH_VMARCHCMD_H */
