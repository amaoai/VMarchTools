/* AUTHOR: TIAN_SHENG, DATE: 2022/7/12 */
#ifndef PUB_INIT_H
#define PUB_INIT_H

#include "opts.h"

#define OPT_DUMP 1
#define OPT_CP   2
#define OPT_PORT 3

static struct option options[] = {
        { "", "dump", optional_argument, OPT_DUMP,
          "打印服务的堆栈日志一般用于排查OOM, 参数：输出文件名，默认 <服务名>.dump" },
        {"config.profile", "cp", required_argument, OPT_CP,
         "设置配置文件profile, 比如 dev/prod" },
        {"", "port", required_argument, OPT_PORT,"配置服务运行端口" },

};

#define CMD_START   0x0001  /* 启动服务 */
#define CMD_STOP    0x0010  /* 停止服务 */
#define CMD_RESTART 0x0100  /* 重启服务 */
#define CMD_PS      0x1000  /* 查看当前正在运行的所有服务信息 */

/* 命令行参数结构体 */
struct option_flags {
    unsigned cmd_flags;     /* 运行命令，可以有多个。比如 pub start:ps */
    char     cp[56];        /* config.profile, 配置文件环境。比如：dev, prod, test */
    unsigned port;          /* 配置运行端口 */
};

#endif /* PUB_INIT_H */
