/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "vmarchcmd.h"
#include <unordered_map>
#include <sstream>
#include <string>
#include "color.h"

void call_java_ps(std::unordered_map<std::string, std::string> *ps_map)
{
    char *p_buf = rcmdexec("jps -l");
    std::stringstream stream(p_buf);
    rcmdexec_free_buffer(p_buf);

    std::string line;
    while (getline(stream, line)) {
        int pos = line.find(" ");
        std::string pid = line.substr(0, pos);
        std::string name = line.substr((pos + 1), line.size());

        if (name == "sun.tools.jps.Jps")
            continue;

        ps_map->insert(std::pair<std::string, std::string>(pid, name));
    }
}

// cmdexec: (ps)
// ================
void vmarch_cmd_exec_ps(std::string &pcmd)
{
    std::unordered_map<std::string, std::string> ps_map; /* pid, name */
    call_java_ps(&ps_map);

    for (auto &ps : ps_map) {
        printf("pid[%s], name[%s]\n", ps.first.c_str(), ps.second.c_str());
    }
}