# AUTHOR: TIAN_SHENG, DATE: 2022/7/11
CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(vmarch)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} .)
INCLUDE_DIRECTORIES(${PROJECT_NAME} include)

# 添加宏定义
ADD_DEFINITIONS(-Dvmarch_enable_debug)

ADD_EXECUTABLE(${PROJECT_NAME}
        main.cpp
        opts.c
        cmdexec.c
        vmarchcmd-init.cpp
        vmarchcmd-exec.cpp
        vmarchio.cpp
        jarfind.cpp
        cmd/start.cpp
        cmd/stop.cpp
        cmd/exec.cpp
        cmd/pak.cpp
        cmd/ps.cpp
        cmd/dump.cpp
        cmd/version.cpp
)