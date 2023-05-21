cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# 添加源文件
set(SOURCES
    MGraph.cpp
    sqstack.cpp
    tu.cpp
)

# 添加头文件路径
include_directories(${CMAKE_SOURCE_DIR})

# 生成可执行文件
add_executable(main ${SOURCES})