# 0. CMake Defs
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

# 1. Project Name
project(newbrush)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)
SET(SUPPORT_TARGETS win32 linux64 linux-arm android qnx64 qnx-aarch64)
IF(WIN32)
	set(TARGET "win32")
ELSEIF("${TARGET}" STREQUAL "")
	MESSAGE(FATAL_ERROR "target is not specified, set var 'TARGET' to one of [${SUPPORT_TARGETS}] using '-DTARGET=xxx'")
ELSE()
	LIST(FIND SUPPORT_TARGETS ${TARGET} RET)
	IF(${RET} EQUAL -1)
		MESSAGE(FATAL_ERROR "unknown target '${TARGET}', set var 'TARGET' to one of [${SUPPORT_TARGETS}] using '-DTARGET=xxx'")
	ENDIF()
ENDIF()

IF("${CMAKE_INSTALL_PREFIX}" STREQUAL "")
	SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist/${TARGET})
ENDIF()
SET(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
IF(ANDROID)
SET(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib/$ENV{ANDROID_ABI})
ELSE()
SET(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
ENDIF()
SET(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
SET(CMAKE_INSTALL_ETCDIR ${CMAKE_INSTALL_PREFIX}/etc)
SET(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_PREFIX}/doc)
SET(CMAKE_DEBUG_POSTFIX d)

IF("${TARGET}" MATCHES "win")
	add_compile_options(/wd4996)
#	add_compile_options(/wd4251)
	add_definitions("-DRTTR_DLL")
ELSEIF("${TARGET}" MATCHES "linux")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF("${TARGET}" MATCHES "android")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing")
ELSEIF("${TARGET}" MATCHES "qnx")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
ENDIF()

SET(3RDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
include_directories(libnb)
include_directories(${3RDPARTY_DIR}/include)
link_directories(${3RDPARTY_DIR}/lib/${TARGET})

# 4. Sub Projects
#src_dir：目录前缀。结果为移除此前缀后的分组
function(group_by_dir src_dir)
  foreach(FILE ${ARGN})
    # 获取文件绝对路径
    get_filename_component(FULL_NAME "${FILE}" ABSOLUTE)
    # 获取文件父路径
    get_filename_component(PARENT_DIR "${FULL_NAME}" PATH)
    # 移除父路径中的源码根路径
    string(REPLACE "${ARGV0}" "" GROUP "${PARENT_DIR}")
    # 确保路径使用windows路径符号
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    # 将文件归组到 "Source Files" 和 "Header Files"
    if("${FILE}" MATCHES ".*\\.h" OR "${FILE}" MATCHES ".*\\.hpp")
      set(GROUP "${GROUP}")
    else()
      set(GROUP "${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
endfunction(group_by_dir)

add_subdirectory(libnb)
add_subdirectory(projects)
if(NOT ANDROID)
add_subdirectory(unittests)
endif()

# 5. Project Install
INSTALL(DIRECTORY ${3RDPARTY_DIR}/include/rttr DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
INSTALL(DIRECTORY ${3RDPARTY_DIR}/include/glm DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
INSTALL(DIRECTORY resource DESTINATION ${CMAKE_INSTALL_PREFIX})

FILE(GLOB LIBS ${3RDPARTY_DIR}/lib/${TARGET}/*.dll ${3RDPARTY_DIR}/lib/${TARGET}/*rttr*.lib ${3RDPARTY_DIR}/lib/${TARGET}/*.so* ${3RDPARTY_DIR}/lib/${TARGET}/*.exe)
INSTALL(FILES ${LIBS} DESTINATION ${CMAKE_INSTALL_LIBDIR})

# 6. Group Projects
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
