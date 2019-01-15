
# 0. CMake Defs

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

cmake_policy(VERSION 2.6)

# 1. Project Name

project(newbrush)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
if(WIN32)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/freetype)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/opengl)
	link_directories(${CMAKE_SOURCE_DIR}/3rdparty/lib/win32)
endif()

# 4. Sub Projects

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(examples)

# 5. Project Install
# N/A
