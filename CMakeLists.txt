cmake_minimum_required(VERSION 3.22)
project(vmarch)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR} include)

add_executable(${PROJECT_NAME}
        main.cpp
        opts/opts.c
        vmarchcmd-init.cpp
        cmd/start.cpp
        cmd/stop.cpp
        cmd/vps.cpp
        vmarchio.cpp
        cmdexec.cpp
        vmarchtools.cpp
)
