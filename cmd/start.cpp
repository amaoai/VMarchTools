/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "declcmd.h"
#include "cmdexec.h"
#include "vmarchio.h"
#include "vmarchtools.h"
#include <sstream>
#include "color.h"

/* 获取当前需要启动的Java文件 */
std::string check_java_file(const std::string *pcmd)
{
    if (!pcmd->empty())
        return *pcmd;

    auto vecfile = find_file(getpcwd(), ".jar");

    if (vecfile.empty())
        vmarchtools::verror("当前目录下没找到可执行JAR包（如果有WAR包等其他格式请手动指定）："
                            "\n  $ vmarch <CMD> <JAR包名 | 进程名>\n");

    if (vecfile.size() > 1) {
        std::stringstream ss;
        ss << "找到多个JAR包，请选择其中一个: ";
        for (auto &file : vecfile)
            ss << file << " ";
        vmarchtools::verror(ss.str());
    }

    return vecfile[0];
}

void cmd_start(const std::string *pcmd, const struct vmarchcmd_flags *flags, VMARCHFLAGS)
{
    std::string jfile = check_java_file(pcmd);
    std::string javaopts = "java";
    std::string logfile = "log.stdout";

    if (flags->vdb > 0)
        javaopts += " -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=" + std::to_string(flags->vdb);

    javaopts += vmarchtools::fmt(" -jar %s", jfile.c_str());

    if (!flags->yml.empty())
        javaopts += " --spring.config.location=" + flags->yml;

    if (!flags->cp.empty())
        javaopts += " --spring.profiles.active=" + flags->cp;

    javaopts += vmarchtools::fmt(" > %s 2>&1 &", logfile.c_str());

    pcmdexec(javaopts);

    if (flags->xtl)
        pcmdexec(vmarchtools::fmt("tail -f %s", logfile.c_str()));
}
