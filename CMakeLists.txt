# AUTHOR: TIAN_SHENG, DATE: 2022/7/11
cmake_minimum_required(VERSION 3.22)
project(vmarch C)

set(CMAKE_C_STANDARD 23)

include_directories(${PROJECT_NAME} .)
include_directories(${PROJECT_NAME} include)

# 添加宏定义
add_definitions(-Dvmarch_enable_debug)

add_executable(${PROJECT_NAME}
        main.c
        opts.c
        vmarch-init.c)
