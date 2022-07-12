/* AUTHOR: TIAN_SHENG, DATE: 2022/7/12 */
#ifndef PUB_INIT_H
#define PUB_INIT_H

#include "opts.h"
#include "pub/typedef.h"

#define CMD_START       ((unsigned) 0X001F)  /* 启动服务 */
#define CMD_STOP        ((unsigned) 0x002F)  /* 停止服务 */
#define CMD_RESTART     ((unsigned) 0x003F)  /* 重启服务 */
#define CMD_PS          ((unsigned) 0x004F)  /* 打印当前服务的运行状态 */
#define CMD_EXEC        ((unsigned) 0x005F)  /* 进入 jar 包内部，并查看文件。vmarch exec exp.jar | vmarch exec */
#define CMD_PACK        ((unsigned) 0x006F)  /* 将服务打包成docker镜像, vmarch pack docker */
#define CMD_DUMP        ((unsigned) 0x007F)  /* 打印服务的堆栈日志一般用于排查OOM, 参数：输出文件名，默认 <服务名>.dump */

#define OPT_NSD          1
#define OPT_CP           2
#define OPT_PORT         3
#define OPT_DEBUG_PORT   4
#define OPT_MONITOR      5

/* 命令的 option 列表 */
const static struct option VMARCH_OPTIONS[] = {
        {"notice-shutdown", "nsd",  no_argument,       OPT_NSD,        "启动检测服务是否宕机"},
        {"conf-profile",    "cp",   required_argument, OPT_CP,         "设置配置文件profile, 比如 dev/prod"},
        {"",                "port", required_argument, OPT_PORT,       "设置服务运行端口"},
        {"",                "dp",   required_argument, OPT_DEBUG_PORT, "设置远程调试端口"},
        {"monitor",         "mon",  no_argument,       OPT_MONITOR,    "监控服务运行情况"},
};

/* 命令行参数结构体。如果不懂什么意思的话：
 * 请根据结构体成员名到 VMARCH_OPTIONS 去找对应的描述 */
struct vmarch_option_flags {
    unsigned cmd_flags;
    BOOL     nsd;
    char     cp[56];
    unsigned port;
    unsigned dp;
    BOOL     mon;
};

/* 参数 flags 指针是函数的返回结构体。
 * 而 vmarch_make_cmdline 的返回值是执行结果是否出现错误 */
int vmarch_make_cmdline(int argc, char **argv, struct vmarch_option_flags *flags);

#endif /* PUB_INIT_H */
