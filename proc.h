/* AUTHOR: TIAN_SHENG, DATE: 2022/7/25 */
#ifndef VMARCH_VPROC_H
#define VMARCH_VPROC_H

#include <string>
#include "cmdexec.h"
#include "vmarchio.h"

VMARCH_API char *__CURENT_SOURCE_DIRECTOR__;
#define SOURCE_DIRECTOR __CURENT_SOURCE_DIRECTOR__

void proc_exec(const std::string &__ProcName, const std::string __Pcmd, std::string &__Pval);

#endif /* VMARCH_VPROC_H */
