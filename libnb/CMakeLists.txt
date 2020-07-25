
# 0. CMake Defs

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

cmake_policy(VERSION 2.6)

# 1. Project Name

project(libnb)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)
set(CMAKE_DEBUG_POSTFIX d)

include_directories(include)
if(WIN32)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/freetype)
	include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/opengl)
	link_directories(${CMAKE_SOURCE_DIR}/3rdparty/lib)
endif()

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
      set(GROUP "Header Files${GROUP}")
    else()
      set(GROUP "Source Files${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
endfunction(group_by_dir)

# 4. Sub Projects
add_subdirectory(src)
add_subdirectory(examples)

# 5. Project Install
install(DIRECTORY include/newbrush DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 6. Group Projects
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET_PROPERTY(TARGET core PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET gles PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET gui PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET rpc-helper PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET nbplayer PROPERTY FOLDER examples)
SET_PROPERTY(TARGET newbrush-tests PROPERTY FOLDER examples)

