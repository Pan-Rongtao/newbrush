
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(rpc-helper)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)
set(GAPI_PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)
set(GAPI_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/gapi)
file(MAKE_DIRECTORY ${GAPI_GEN_DIR})
set(PROTO_PATH ${GAPI_PROTO_DIR}/../../../../3rdparty/include/grpc/)
set(TOOLDIR ${CMAKE_SOURCE_DIR}/tools)

include(${GAPI_PROTO_DIR}/GRPC-API-GEN.cmake)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/grpc)
include_directories(${GAPI_GEN_DIR})
add_definitions(-D_WIN32_WINNT=0x600)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# 3. Project Build
set(LIB_NAME "rpc-helper")

file(GLOB_RECURSE GAPI_GEN_INC_LIST ${GAPI_GEN_DIR}/*.h)
file(GLOB_RECURSE GAPI_GEN_SRC_LIST ${GAPI_GEN_DIR}/*.cpp ${GAPI_GEN_DIR}/*.cc)
file(GLOB_RECURSE INC_LIST *.h)
file(GLOB_RECURSE SRC_LIST *.cpp)

if(WIN32)
	group_by_dir(${CMAKE_CURRENT_BINARY_DIR} ${GAPI_GEN_INC_LIST})
	group_by_dir(${CMAKE_CURRENT_BINARY_DIR} ${GAPI_GEN_SRC_LIST})
	group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${INC_LIST})
	group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_LIST})
endif()

add_library(${LIB_NAME} STATIC ${GAPI_GEN_INC_LIST} ${GAPI_GEN_SRC_LIST} ${INC_LIST} ${SRC_LIST})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME ${LIB_NAME})

target_link_libraries(${LIB_NAME} core media gles gui 
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
#install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
#install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
