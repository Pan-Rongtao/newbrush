
# 0. CMake Defs

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

cmake_policy(VERSION 2.6)

# 1. Project Name

project(newbrush)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)
set(CMAKE_DEBUG_POSTFIX d)

if(UNIX)
	if ("${CMAKE_SYSTEM_NAME}" STREQUAL QNX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

if ("${CMAKE_INSTALL_PREFIX}" STREQUAL "")
	SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist)
endif()
SET(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
SET(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
SET(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
SET(CMAKE_INSTALL_ETCDIR ${CMAKE_INSTALL_PREFIX}/etc)
SET(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_PREFIX}/doc)

include_directories(include)
if(WIN32)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/freetype)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/opengl)
	link_directories(${CMAKE_SOURCE_DIR}/3rdparty/lib)
#	if(CMAKE_CL_64)
#		link_directories(${CMAKE_SOURCE_DIR}/3rdparty/lib/win64)
#	else(CMAKE_CL_64)
#		link_directories(${CMAKE_SOURCE_DIR}/3rdparty/lib/win32)
#	endif(CMAKE_CL_64)
endif()

# 4. Sub Projects

add_subdirectory(3rdparty)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(examples)

# 5. Project Install
# N/A
