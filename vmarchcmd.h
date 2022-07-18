/* AUTHOR: TIAN_SHENG, DATE: 2022/7/12 */
#ifndef VMARCH_CMD_INIT_H
#define VMARCH_CMD_INIT_H

#include "opts.h"
#include "tool/array.h"
#include "typedef.h"
#include "vmarchio.h"
#include <string>
#include <string.h>

#define BIT(x) 1 << (x)

#define VMARCHCMD_NULL    BIT(0)  /* 没有命令 */
#define VMARCHCMD_START   BIT(1)  /* 启动服务 */
#define VMARCHCMD_STOP    BIT(2)  /* 停止服务 */
#define VMARCHCMD_RESTART BIT(3)  /* 重启服务 */
#define VMARCHCMD_PS      BIT(4)  /* 打印当前服务的运行状态 */
#define VMARCHCMD_EXEC    BIT(5)  /* 进入 jar 包内部，并查看文件。vmarch exec exp.jar | vmarch exec */
#define VMARCHCMD_PAK     BIT(6)  /* 将服务打包成docker镜像, vmarch pack docker */
#define VMARCHCMD_DUMP    BIT(7)  /* 打印服务的堆栈日志一般用于排查OOM, 参数：输出文件名，默认 <服务名>.dump */
#define VMARCHCMD_VERSION BIT(8)  /* 打印版本号 */

/* cmd类型定义 */
#define VMARCHCMD unsigned

#define OPT_NSD          1
#define OPT_CP           2
#define OPT_PORT         3
#define OPT_DEBUG_PORT   4
#define OPT_MONITOR      5
#define OPT_XTAIL        6
#define OPT_VERSION      7

/* 命令的 option 列表 */
const static struct option VMARCH_OPTIONS[] = {
        {"notice-shutdown", "nsd",  optional_argument, OPT_NSD,        "启动检测服务是否宕机"},
        {"conf-profile",    "cp",   required_argument, OPT_CP,         "设置配置文件profile, 比如 dev/prod"},
        {"",                "port", required_argument, OPT_PORT,       "设置服务运行端口"},
        {"debug-port",      "dp",   required_argument, OPT_DEBUG_PORT, "设置远程调试端口"},
        {"monitor",         "mon",  no_argument,       OPT_MONITOR,    "监控服务运行情况"},
        {"xtail",           "xtl",  no_argument,       OPT_XTAIL,      "运行服务并打印日志"},
        {"version",         "v",    no_argument,       OPT_VERSION,    "打印版本号"},
};

/* 命令行参数结构体。如果不懂什么意思的话：
 * 请根据结构体成员名到 VMARCH_OPTIONS 去找对应的描述 */
struct vmarch_option_flags {
    VMARCHCMD cmd;
    char      nsd[256];
    char      cp[64];
    char      port[5];
    char      dp[5];
    BOOL      mon;
    BOOL      xtl;
    BOOL      v;
};

#define vmarch_option_flags_printf(p_optflags)        \
    printf("vmarch_option_flags:\n\t"                 \
        "cmd: %d\n\t"                                 \
        "nsd: %s\n\t"                                 \
        "cp: %s\n\t"                                  \
        "port: %s\n\t"                                \
        "dp: %s\n\t"                                  \
        "mon: %d\n",                                  \
        (p_optflags->cmd),                            \
        (p_optflags->nsd),                            \
        (p_optflags->cp),                             \
        (p_optflags->port),                           \
        (p_optflags->dp),                             \
        (p_optflags->mon)                             \
    )

void vmarch_make_cmdline(int argc, char **argv, struct vmarch_option_flags *flags); /* 参数 flags 指针是函数的返回结构体。*/
void vmarchcmd_exec(const struct vmarch_option_flags *p_optflags); /* 执行命令 */

#endif /* VMARCH_CMD_INIT_H */
