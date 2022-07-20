/* AUTHOR: TIAN_SHENG, DATE: 2022/7/19 */
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

/* 打印错误信息 */
void verror(const char *fmt, ...)
{
    va_list vp;
    va_start(vp, fmt);
    vfprintf(stderr, fmt, vp);
    va_end(vp);

    exit(-1);
}