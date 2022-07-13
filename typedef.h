/* AUTHOR: TIAN_SHENG, DATE: 2022/7/12 */
#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include <stdlib.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#ifdef linux
#  define _MAX_FILE_NAME 1024
#elif WIN32
#  define _MAX_FILE_NAME 260
#endif

#endif /* _TYPEDEF_H */
