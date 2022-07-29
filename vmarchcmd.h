/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHCMD_H
#define VMARCH_VMARCHCMD_H

#include "opts/opts.h"
#include <cstdlib>
#include <string>

#define VMARCHCMD int
#define VMARCHFLAGS int

/* flags */
#define VMARCHFLAGS_NO_FALGS 0
#define VMARCHFLAGS_STOP_JUST_STOP  ( 1 << 0 )
#define VMARCHFLAGS_STOP_RESTART    ( 1 << 1 )

/* cmds */
#define VMARCHCMD_START             0x00000001
#define VMARCHCMD_RESTART           0x00000010
#define VMARCHCMD_STOP              0x00000100
#define VMARCHCMD_PS                0x00001000
#define VMARCHCMD_STATUS            0x00010000

#define OPTVAL_HELP                 0

#define OPTVAL_START_XTL            1
#define OPTVAL_START_VDB            2
#define OPTVAL_START_YML            3
#define OPTVAL_START_CP             4

#define OPTVAL_STATUS_DETAIL        1

/* 未知命令 */
inline static void verror_unknown_cmd(const std::string& cmd) {
    fprintf(stderr, "unknown command: %s\n", cmd.c_str());
    exit(EXIT_FAILURE);
}

const static struct option vmarch_cmd_start_options[] = {
        {"help", "h", no_argument, OPTVAL_HELP, "显示帮助信息"},
        {"tail", "xtl", no_argument, OPTVAL_START_XTL, "打印程序执行日志"},
        {"", "vdb", required_argument, OPTVAL_START_VDB, "远程调试端口"},
        {"", "yml", required_argument, OPTVAL_START_YML, "指定配置文件路径"},
        {"", "cp", required_argument, OPTVAL_START_CP, "指定配置文件后缀"}
};

const static struct option vmarch_cmd_status_options[] = {
        {"help", "h", no_argument, OPTVAL_HELP, "显示帮助信息"},
        {"detail", "d", optional_argument, OPTVAL_STATUS_DETAIL, "查看进程详细内容"},
};

struct vmarchcmd_flags {
    bool xtl;
    int vdb;
    std::string yml;
    std::string cp;
    std::string detail;
};

void vmarchcmd_main(int argc, char **argv);

#endif /* VMARCH_VMARCHCMD_H */
