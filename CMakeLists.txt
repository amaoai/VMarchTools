# AUTHOR: TIAN_SHENG, DATE: 2022/7/11
cmake_minimum_required(VERSION 3.22)
project(vmarch C)

set(CMAKE_C_STANDARD 23)

include_directories(${PROJECT_NAME} include)

add_executable(pub main.c opts.c)
