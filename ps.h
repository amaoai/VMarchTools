/* AUTHOR: TIAN_SHENG, DATE: 2022/7/25 */
#ifndef VMARCH_PROCINFO_H
#define VMARCH_PROCINFO_H

#include <string>
#include <sstream>
#include "proc.h"

struct psval_info {
    unsigned long pid;
    std::string name;
    float cpu;
    float mem;
    std::vector<std::string> protvec;
};

void getps(std::vector<struct psval_info> *p_psvalvec);

#endif /* VMARCH_PROCINFO_H */
