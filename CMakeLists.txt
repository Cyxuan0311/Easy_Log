cmake_minimum_required(VERSION 3.10)
project(Easy_Log)

set(CMAKE_CXX_STANDARD 11)

# 查找FTXUI库
find_package(ftxui REQUIRED)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加可执行文件
add_executable(${PROJECT_NAME}
    src/main.cpp         # 主程序在src目录
    include/Logger.cpp   # 实现文件在include目录
)

# 链接FTXUI库
target_link_libraries(${PROJECT_NAME} ftxui::screen ftxui::dom ftxui::component)