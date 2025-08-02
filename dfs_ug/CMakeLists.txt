# 设置最低要求的 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和版本号
project(dfs VERSION 1.0.0 LANGUAGES C CXX)

# 设置 C/C++ 标准（可选）
set(CMAKE_C_STANDARD 11)    # 设置 C 标准为 C11
set(CMAKE_CXX_STANDARD 17)  # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制要求标准
set(CMAKE_CXX_EXTENSIONS OFF)       # 禁用编译器特定扩展

# 设置构建类型（Debug 或 Release），默认 Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# 定义用户可配置选项
option(BUILD_TESTS "Build the unit tests" OFF)      # 是否构建测试
option(ENABLE_FEATURE "Enable a cool feature" ON)   # 是否启用某个功能

# 设置输出目录（可选）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # 可执行文件输出到 bin/
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 动态库输出到 lib/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 静态库输出到 lib/

# 添加源文件
set(SOURCES
    dfs.c           # 主程序文件
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})


# 打印一些调试信息（可选）
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Enable Feature: ${ENABLE_FEATURE}")
