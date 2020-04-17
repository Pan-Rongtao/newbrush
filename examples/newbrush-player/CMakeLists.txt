
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(newbrush-player)

set(GAPI_PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)
include(${GAPI_PROTO_DIR}/GRPC-API-GEN.cmake)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/grpc)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-D_WIN32_WINNT=0x600)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# 3. Project Build
set(BIN_NAME "nbplayer")

function(group_by_dir src_dir)
  foreach(FILE ${ARGN})
    # 获取文件绝对路径
    get_filename_component(FULL_NAME "${FILE}" ABSOLUTE)
    # 获取文件父路径
    get_filename_component(PARENT_DIR "${FULL_NAME}" PATH)
    # 移除父路径中的源码根路径
    string(REPLACE "${PARENT_DIR}" "" FileName "${FULL_NAME}")
    # 确保路径使用windows路径符号
    string(REPLACE "/" "\\" GROUP "${GROUP}")
	message(STATUS ${FileName})
    # 将文件归组到 "Source Files" 和 "Header Files"
    if("${FILE}" MATCHES ".*build")
      set(GROUP "\\gapi")
	else()
      set(GROUP "")
	endif()
	  
    if("${FILE}" MATCHES ".*\\.h")
      set(GROUP "Header Files${GROUP}")
    else()
      set(GROUP "Source Files${GROUP}")
    endif()
	message(STATUS ${GROUP})
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
endfunction(group_by_dir)

file(GLOB INC_LIST *.h ${CMAKE_CURRENT_BINARY_DIR}/*.h)
file(GLOB SRC_LIST *.cpp ${CMAKE_CURRENT_BINARY_DIR}/*.cc)
if(WIN32)
	group_by_dir("${CMAKE_CURRENT_SOURCE_DIR}" ${INC_LIST})
	group_by_dir("${CMAKE_CURRENT_SOURCE_DIR}" ${SRC_LIST})
endif()
#file(GLOB SRC_FILES "*.h" "*.cpp" ${CMAKE_CURRENT_BINARY_DIR}/*.h ${CMAKE_CURRENT_BINARY_DIR}/*.cc)

add_executable(${BIN_NAME} ${INC_LIST} ${SRC_LIST})
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME ${BIN_NAME})

target_link_libraries(${BIN_NAME} core media gles gui 
optimized libprotobuf debug libprotobufd
optimized grpc debug grpcd
optimized gpr debug gprd
optimized grpc++ debug grpc++d
optimized ssl debug ssld
optimized crypto debug cryptod
optimized cares debug caresd
optimized zlibstatic debug zlibstaticd
optimized address_sorting debug address_sortingd
optimized upb debug upbd
optimized absl_strings debug absl_stringsd
optimized absl_throw_delegate debug absl_throw_delegated
)

# 4. Project Install
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
