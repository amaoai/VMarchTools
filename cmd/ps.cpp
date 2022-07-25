/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include "ps.h"
#include "vmarchcmd.h"

void psval_init(std::string pcmd, std::vector<struct psval_info> *psvec)
{
    std::string xpsout;
    proc_exec("xps", pcmd, xpsout);

    /* 解析xps输出 */
    std::stringstream xpsout_stream(xpsout);

    std::string line;
    struct psval_info psv0;
    bool is_first = true;

    while (getline(xpsout_stream, line)) {
        /* 主节点：进程数据 */
        if (line[0] != ' ') {
            if (!is_first)
                psvec->push_back(psv0);
            else
                is_first = false;

            psv0 = {};
            std::stringstream line_stream(line);
            line_stream >> psv0.pid;
            line_stream >> psv0.name;
            line_stream >> psv0.cpu;
            line_stream >> psv0.mem;
            goto NEXT_LINE;
        }

        /* 子节点：端口 */
        if (line[1] == ' ') {
            std::string protocol;
            std::string port;
            std::stringstream line_stream(line);
            line_stream >> protocol;
            line_stream >> port;
            psv0.protvec.push_back(protocol + "/" + port);
            goto NEXT_LINE;
        }

        NEXT_LINE:
        continue;
    }

    psvec->push_back(psv0);
}

void getps(std::vector<struct psval_info> *p_psvalvec)
{
    psval_init("", p_psvalvec);
}

// cmdexec: (ps)
// ================
void vmarch_cmd_exec_ps(std::string &pcmd)
{
    std::vector<struct psval_info> psvalinfo_vec;
    getps(&psvalinfo_vec);

    for (auto &psval : psvalinfo_vec)
        printf("%lu %s %s\n", psval.pid, psval.name.c_str(), psval.protvec[0].c_str());
}