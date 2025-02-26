cmake_minimum_required(VERSION 3.10)
project(yazi-log)

set(CMAKE_CXX_STANDARD 11)
# include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp         # 主程序在src目录
    include/Logger.cpp   # 实现文件在include目录
)