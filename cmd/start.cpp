/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "declcmd.h"
#include "cmdexec.h"
#include "vmarchio.h"
#include "vmarchtools.h"
#include <stdexcept>
#include <sstream>
#include "color.h"

/* 获取当前需要启动的Java文件 */
std::string check_file(const std::string *pcmd)
{
    if (!pcmd->empty())
        return *pcmd;

    auto vecfile = find_file(getpcwd(), ".jar");

    if (vecfile.empty())
        throw std::runtime_error("no jar file found");

    if (vecfile.size() > 1) {
        std::stringstream ss;
        ss << "more than one jar file found, please select one: ";
        for (auto &file : vecfile)
            ss << file << " ";
        throw std::runtime_error(ss.str());
    }

    return vecfile[0];
}

void cmd_start(const std::string *pcmd, const struct vmarchcmd_flags *flags)
{
    std::string jfile = check_file(pcmd);
    std::string javaopts = "java";

    if (flags->vdb > 0)
        javaopts += " -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=" + std::to_string(flags->vdb);

    if (!flags->cp.empty())
        javaopts += " -Dspring.config.active=" + flags->cp;

    if (flags->xtl)
        pcmdexec(vmarchtools::fmt("tail -f %s.log.stdout"));

    printf("vmarchtools: start java application: %s%s%s\n", VMARCH_COLOR_RED, jfile.c_str(), VMARCH_COLOR_RESET);
}
