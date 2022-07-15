# AUTHOR: TIAN_SHENG, DATE: 2022/7/11
CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(vmarch)

SET(CMAKE_CXX_STANDARD 23)

# 指定编译哪个系统下的源码文件
SET(OS_FILE_SOURCE "")

INCLUDE_DIRECTORIES(${PROJECT_NAME} .)
INCLUDE_DIRECTORIES(${PROJECT_NAME} include)

# 添加宏定义
ADD_DEFINITIONS(-Dvmarch_enable_debug)

ADD_EXECUTABLE(${PROJECT_NAME}
        main.cpp
        opts.c
        vmarchcmd-init.cpp
        vmarchcmd-exec.cpp
        vmarchio.cpp
        systemctl.c
        c/start.cpp
        c/stop.cpp
)