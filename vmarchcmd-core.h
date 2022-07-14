/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13
 *
 * CMD核心头文件，包含所有命令定义以及调试工具的定义。
 *
 *   一段CMD的命令在 vmarch_make_cmdline(int, char **, struct vmarch_option_flags *) 函数中被解析。
 * 解析的结果通过指针赋值到 struct vmarch_option_flags 结构体中。
 *
 * 在这里的命令是定义的什么（使用docker命令演示）?
 *
 *     比如执行一段 docker 启动容器的脚本 -> docker start <ImageID> -d
 *                                                 ^              ^
 *
 * 上面的脚本中 start 就是指的命令，而 -d 是选项。
 *
 */
#ifndef VMARCH_VMARCHCMD_CORE_H
#define VMARCH_VMARCHCMD_CORE_H

#include "opts.h"
#include "tool/array.h"
#include "typedef.h"
#include "vmarchio.h"

#define VMARCHCMD_NULL    0x00000000  /* 没有命令 */
#define VMARCHCMD_START   0x00000001  /* 启动服务 */
#define VMARCHCMD_STOP    0x00000010  /* 停止服务 */
#define VMARCHCMD_RESTART 0x00000100  /* 重启服务 */
#define VMARCHCMD_PS      0x00001000  /* 打印当前服务的运行状态 */
#define VMARCHCMD_EXEC    0x00010000  /* 进入 jar 包内部，并查看文件。vmarch exec exp.jar | vmarch exec */
#define VMARCHCMD_PACK    0x00100000  /* 将服务打包成docker镜像, vmarch pack docker */
#define VMARCHCMD_DUMP    0x01000000  /* 打印服务的堆栈日志一般用于排查OOM, 参数：输出文件名，默认 <服务名>.dump */

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
    char      nsd[256];
    char      cp[64];
    unsigned  port;
    unsigned  dp;
    BOOL      mon;
};

#define vmarch_option_flags_printf(p_optflags)        \
    printf("vmarch_option_flags:\n\t"                 \
        "cmd: %d\n\t"                                 \
        "nsd: %s\n\t"                                 \
        "cp: %s\n\t"                                  \
        "port: %d\n\t"                                \
        "dp: %d\n\t"                                  \
        "mon: %d\n",                                  \
        (p_optflags->cmd),                            \
        (p_optflags->nsd),                            \
        (p_optflags->cp),                             \
        (p_optflags->port),                           \
        (p_optflags->dp),                             \
        (p_optflags->mon)                             \
    )

/* 参数 flags 指针是函数的返回结构体。*/
void vmarch_make_cmdline(int argc, char **argv, struct vmarch_option_flags *flags);

#endif /* VMARCH_VMARCHCMD_CORE_H */
