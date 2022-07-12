/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#include "opts.h"
#include <stdio.h>
#include <string.h>

#define NOT_OPT   0                 /* 不是命令行选项 */
#define SHORT_OPT 1                 /* 短选项 */
#define LONG_OPT  2                 /* 长选项 */

char *optarg;
char *optopt;
int   opterr = OPTERR_NO_ERR;


/* 0表示不是选项，1表示短选项，2表示长选项 */
int is_opt(const char *ch)
{
    if (ch[0] != '-')
        return NOT_OPT;

    return ch[1] == '-' ? LONG_OPT : SHORT_OPT;
}

const struct option *find_option(char *curch, int typ, const struct option *options, int size)
{
    const char          *cmp_ch;
    const struct option *opt = NULL;

    /* 短选项，curch + 1。
     * 比如字符是：-version, 偏移一位后就是 version
     *
     * 如果是长选项，就再偏移一位, curch + 2 */
    curch = typ == SHORT_OPT ? curch + 1 : curch + 2;

    for (int i = 0; i < size; i++) {
        opt = &options[i];

        cmp_ch = typ == SHORT_OPT ? opt->short_name : opt->long_name;

        if (strcmp(cmp_ch, curch) == 0)
            goto FIND_OPTION_END;

        opt = NULL;
    }

FIND_OPTION_END:
    return opt;
}

/* 参数查找，如果没有找到返回NULL */
char *find_argument(int argc, char **argv, int *optidx, char *optch, const struct option *p_opt)
{
    char *_optarg_tmp = NULL;

    switch (p_opt->has_arg) {
        /* 必填参数 */
        case required_argument: {
            /* 因为选项参数是在当前命令的下一个位置。所以这里optidx需要+1 */
            if ((++*optidx) < argc) {
                _optarg_tmp = argv[*optidx];
                /* 如果参数是option抛出错误, 因为option不能作为参数 */
                if (is_opt(_optarg_tmp))
                    _optarg_tmp = NULL;
            }

            if (_optarg_tmp == NULL) {
                opterr = OPTERR_NO_ARGUMENT;
                printf("%s 选项需要包含参数\n", optch);
            }

            break;
        }

        /* 可选参数 */
        case optional_argument: {
            int argidx = *optidx + 1;

            if (argidx < argc) {
                _optarg_tmp = argv[argidx];
                if (is_opt(_optarg_tmp))
                    _optarg_tmp = NULL;
            }

            if (_optarg_tmp != NULL)
                ++*optidx;

            break;
        }
    }

    return _optarg_tmp;
}

int getopts(int argc, char **argv, const struct option *options, int size, int *p_optval)
{
    static int optidx = 1;
    const struct option *p_opt;

    *p_optval = OPT_ALL;

    if (optidx < argc) {
        optopt = argv[optidx];

        /* 判断选项类型: not opt, long opt, short opt */
        int opttyp = is_opt(optopt);

        /* 如果是选项的话去匹配已经定义好的option数组 */
        if (opttyp) {
            p_opt = find_option(optopt, opttyp, options, size);

            if (p_opt != NULL) {
                *p_optval = p_opt->optval;
                /* 查找参数 */
                optarg = find_argument(argc, argv, &optidx, optopt, p_opt);
            }
        }

        if (opterr != OPTERR_NO_ERR)
            return -1;

        return (++optidx);
    }

    return -1;
}