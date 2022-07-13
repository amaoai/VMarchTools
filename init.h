/* AUTHOR: TIAN_SHENG, DATE: 2022/7/12 */
#ifndef PUB_INIT_H
#define PUB_INIT_H

#include "opts.h"
#include "vmarch/tool/array.h"
#include "vmarch/tool/typedef.h"

#define VMARCHCMD_NULL    ((unsigned) 1)       /* 没有命令 */
#define VMARCHCMD_START   ((unsigned) 1 << 1)  /* 启动服务 */
#define VMARCHCMD_STOP    ((unsigned) 1 << 2)  /* 停止服务 */
#define VMARCHCMD_RESTART ((unsigned) 1 << 3)  /* 重启服务 */
#define VMARCHCMD_PS      ((unsigned) 1 << 4)  /* 打印当前服务的运行状态 */
#define VMARCHCMD_EXEC    ((unsigned) 1 << 5)  /* 进入 jar 包内部，并查看文件。vmarch exec exp.jar | vmarch exec */
#define VMARCHCMD_PACK    ((unsigned) 1 << 6)  /* 将服务打包成docker镜像, vmarch pack docker */
#define VMARCHCMD_DUMP    ((unsigned) 1 << 7)  /* 打印服务的堆栈日志一般用于排查OOM, 参数：输出文件名，默认 <服务名>.dump */

/* cmd类型定义 */
#define VMARCHCMD unsigned

#define OPT_NSD          1
#define OPT_CP           2
#define OPT_PORT         3
#define OPT_DEBUG_PORT   4
#define OPT_MONITOR      5

/* 命令的 option 列表 */
const static struct option VMARCH_OPTIONS[] = {
        {"notice-shutdown", "nsd",  optional_argument, OPT_NSD,        "启动检测服务是否宕机"},
        {"conf-profile",    "cp",   required_argument, OPT_CP,         "设置配置文件profile, 比如 dev/prod"},
        {"",                "port", required_argument, OPT_PORT,       "设置服务运行端口"},
        {"debug-port",      "dp",   required_argument, OPT_DEBUG_PORT, "设置远程调试端口"},
        {"monitor",         "mon",  no_argument,       OPT_MONITOR,    "监控服务运行情况"},
};

/* 命令行参数结构体。如果不懂什么意思的话：
 * 请根据结构体成员名到 VMARCH_OPTIONS 去找对应的描述 */
struct vmarch_option_flags {
    VMARCHCMD cmd;
    BOOL      nsd;
    char      nsd_val[255];
    char      cp[56];
    unsigned  port;
    unsigned  dp;
    BOOL      mon;
};

/* 初始化结构体 */
static inline void vmarch_init_option_flags(struct vmarch_option_flags *flags)
{
    flags->nsd = FALSE;
    flags->port = 0;
    flags->dp = 0;
    flags->mon = FALSE;
}

/* 参数 flags 指针是函数的返回结构体。
 * 而 vmarch_make_cmdline 的返回值是执行结果是否出现错误 */
int vmarch_make_cmdline(int argc, char **argv, struct vmarch_option_flags *flags);

#endif /* PUB_INIT_H */
