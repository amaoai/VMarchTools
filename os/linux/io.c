/* AUTHOR: TIAN_SHENG, DATE: 2022/7/13 */
#include "vmarchio.h"

#include <string.h>
#include <dirent.h>
#include <malloc.h>

VMARCHFILE *ls(char *path, int *size)
{
    DIR             *dir;
    struct dirent   *p_dirent;
    int              vfsize;
    VMARCHFILE      *vfs;
    int              curidx;

    curidx = 0;
    vfsize = 6;
    vfs    = malloc(sizeof(VMARCHFILE) * vfsize);

    if ((dir = opendir(path)) == NULL) {
        perror("open file dir failed.");
        exit(-1);
    }

    while ((p_dirent = readdir(dir)) != NULL) {

        /* 如果是当前目录或者是父目录就跳过 */
        if (_IGNORE_DIR(p_dirent->d_name))
            continue;

        /* 扩容 */
        if (curidx >= vfsize)
            vfs = realloc(vfs, sizeof(VMARCHFILE) * (vfsize += 2));

        VMARCHFILE *vf = &vfs[curidx];
        strcpy(vf->name, p_dirent->d_name);
        vf->dir = p_dirent->d_type & DT_DIR ? TRUE : FALSE;

        ++curidx;
    }

    closedir(dir);

    *size = curidx;
    return vfs;
}

void vmarchio_free_files(VMARCHFILE *p_files)
{
    free(p_files);
}