# AUTHOR: TIAN_SHENG, DATE: 2022/7/11
CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(vmarch)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} . cmdexec opts proc)

# 添加宏定义
ADD_DEFINITIONS(-Dvmarch_enable_debug)

# 不同平台的源码
SET(PLATFORM_SOURCE "")

MESSAGE(STATUS "Current System Name: ${CMAKE_SYSTEM_NAME}")
IF(${CMAKE_SYSTEM_NAME} MATCHES Linux)
    AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/platform/linux CURRENT_PLATFORM_SOURCE)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES WIN32)
    AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/platform/win32 CURRENT_PLATFORM_SOURCE)
ENDIF()

ADD_EXECUTABLE(${PROJECT_NAME}
        main.cpp
        opts/opts.c
        cmdexec/cmdexec.c
        ${CURRENT_PLATFORM_SOURCE}
        vmarchcmd-init.cpp
        vmarchcmd-exec.cpp
        vmarchio.cpp
        jarfind.cpp
        cmd/start.cpp
        cmd/restart.cpp
        cmd/stop.cpp
        cmd/exec.cpp
        cmd/pak.cpp
        cmd/ps.cpp
        cmd/dump.cpp
        cmd/version.cpp
)