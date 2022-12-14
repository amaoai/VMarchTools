/* AUTHOR: TIAN_SHENG, DATE: 2022/7/11 */
#ifndef __OPTS_H__
#define __OPTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define no_argument 0           /* 不需要参数 */
#define required_argument 1     /* 需要参数, 参数使用空格分割。-cnf dev */
#define optional_argument 2     /* 可选参数 */

#define OPTERR_NO_ERR        0  /* 没有错误 */
#define OPTERR_NO_ARGUMENT (-1) /* 没有参数错误 */

#define OPT_NOT_OPT ('!')       /* 不是一个选项 */
#define OPT_UNKNOWN ('?')       /* 未知选项 */

extern char *xoptarg;           /* 当前命令行的参数内容 */
extern char *xoptopt;           /* 当前命令行opt内容 */
extern int   xopterr;           /* 错误代码 */

/* 通过构建option结构体来解析命令行参数
 * 像这样: static const struct option options[] = {} */
struct option {
    char long_name[20];
    char short_name[10];
    int has_arg;
    int optval;
    char comment[255];
};

/* 遍历命令行参数，并通过p_optval匹配 */
extern int getopts(int argc, char **argv, const struct option *options, int size, int *p_optval);
extern void getopts_show_help(const char *title, const struct option *options, int size);

#ifdef __cplusplus
}
#endif

#endif /* __OPTS_H__ */
