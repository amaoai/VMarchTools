/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include <stdio.h>
#include "opts.h"
#include "tool/array.h"

/* 启动并打印log */
#define OPT_L 0xAE01
#define OPT_X 0xAE02
#define OPT_A 0xAE03

static struct option options[] = {
        { "logs", "l", required_argument, OPT_L },
        { "xfp", "xfp", required_argument, OPT_X },
        { "apx", "a", required_argument, OPT_A },
};

int main(int argc, char **argv)
{
    int opt;

    while(getopts(argc, argv, options, ARRAY_SIZE(options), &opt) != -1) {
        switch(opt) {
            case OPT_L:
                printf("opt -l. %s\n", optarg);
                break;
            case OPT_X:
                printf("opt -xfp. %s\n", optarg);
                break;
            case OPT_A:
                printf("opt -a. %s\n", optarg);
                break;
        }
    }

    return 0;
}
