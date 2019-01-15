
# 0. CMake Defs

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

cmake_policy(VERSION 2.6)

# 1. Project Name

project(3rdparty)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)


# 4. Sub Projects
add_subdirectory(include)
add_subdirectory(lib)


# 5. Project Install
# N/A
