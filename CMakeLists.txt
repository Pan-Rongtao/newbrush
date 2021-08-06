# 0. CMake Defs
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)
 
# 1. Project Name
project(newbrush)

option( BUILD_SHARED_LIBS "Build package with shared libraries." ON )

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)
set(SUPPORT_TARGETS win32 linux64 linux-arm android qnx64 qnx-aarch64)
if(WIN32)
	set(TARGET "win32")
elseif("${TARGET}" STREQUAL "")
	message(FATAL_ERROR "target is not specified, set var 'TARGET' to one of [${SUPPORT_TARGETS}] using '-DTARGET=xxx'")
else()
	list(FIND SUPPORT_TARGETS ${TARGET} RET)
	if(${RET} EQUAL -1)
		message(FATAL_ERROR "unknown target '${TARGET}', set var 'TARGET' to one of [${SUPPORT_TARGETS}] using '-DTARGET=xxx'")
	endif()
endif()

if("${CMAKE_INSTALL_PREFIX}" STREQUAL "")
	set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist/${TARGET})
endif()
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
if(ANDROID)
	set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib/$ENV{ANDROID_ABI})
else()
	set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()
set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INSTALL_ETCDIR ${CMAKE_INSTALL_PREFIX}/etc)
set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_PREFIX}/doc)
set(CMAKE_DEBUG_POSTFIX d)

if("${TARGET}" MATCHES "win")
	add_compile_options(/wd4996)
	add_definitions("-DRTTR_DLL")
elseif("${TARGET}" MATCHES "linux")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif("${TARGET}" MATCHES "android")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing")
elseif("${TARGET}" MATCHES "qnx")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

set(3RDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
include_directories(libnb)
include_directories(${3RDPARTY_DIR}/include)
link_directories(${3RDPARTY_DIR}/lib/${TARGET})

# 4. Sub Projects
# src_dir：目录前缀。结果为移除此前缀后的分组
function(group_by_dir src_dir)
	foreach(FILE ${ARGN})
		get_filename_component(FULL_NAME "${FILE}" ABSOLUTE)			# 获取文件绝对路径
		get_filename_component(PARENT_DIR "${FULL_NAME}" PATH)			# 获取文件父路径
		string(REPLACE "${ARGV0}" "" GROUP "${PARENT_DIR}")				# 移除父路径中的源码根路径
		string(REPLACE "/" "\\" GROUP "${GROUP}")						# 确保路径使用windows路径符号
		if("${FILE}" MATCHES ".*\\.h" OR "${FILE}" MATCHES ".*\\.hpp")	# 将文件归组到 "Source Files" 和 "Header Files"
			set(GROUP "${GROUP}") 
		else()
			set(GROUP "${GROUP}")
		endif()
		source_group("${GROUP}" FILES "${FILE}")
	endforeach()
endfunction(group_by_dir)

# 获取imgui源码
# imgui_path，imgui的路径；ret为结果
function(get_imgui_src imgui_path ret)
	include_directories(${imgui_path})
	include_directories(${imgui_path}/imgui)
	file(GLOB_RECURSE IMGUI_SRC_LIST ${imgui_path}/*.h ${imgui_path}/*.cpp ${imgui_path}/*.hpp ${imgui_path}/*.c)
	group_by_dir(${imgui_path} ${IMGUI_SRC_LIST})

	set(${ret} ${IMGUI_SRC_LIST})
	set(${ret} ${${ret}} PARENT_SCOPE)
endfunction()

add_subdirectory(libnb)
add_subdirectory(projects)
add_subdirectory(unittests)

# 5. Project Install
install(DIRECTORY ${3RDPARTY_DIR}/include/rttr DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/glm DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/catch2 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/effolkronium DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/spdlog DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/imgui DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/IconFontCpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/glad DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${3RDPARTY_DIR}/include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY resource DESTINATION ${CMAKE_INSTALL_PREFIX})
file(GLOB LIBS ${3RDPARTY_DIR}/lib/${TARGET}/*.dll ${3RDPARTY_DIR}/lib/${TARGET}/*rttr*.lib ${3RDPARTY_DIR}/lib/${TARGET}/*.so* ${3RDPARTY_DIR}/lib/${TARGET}/*.exe)
install(FILES ${LIBS} DESTINATION ${CMAKE_INSTALL_LIBDIR})

# 6. Group Projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
