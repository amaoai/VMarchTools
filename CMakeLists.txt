CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(vmarch)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} . opts cmdexec)

ADD_EXECUTABLE(${PROJECT_NAME}
        main.cpp
        opts/opts.c
        vmarchcmd.cpp
        tools.cpp
        cmdexec.cpp
        platform/linux/ffind.cpp
        cmd/start.cpp
        cmd/stop.cpp
        cmd/ps.cpp
        cmd/dump.cpp
)
