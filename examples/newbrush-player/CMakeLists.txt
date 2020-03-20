
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

file(GLOB SRC_FILES "*.h" "*.cpp" ${CMAKE_CURRENT_BINARY_DIR}/*.h ${CMAKE_CURRENT_BINARY_DIR}/*.cc)

add_executable(${BIN_NAME} ${SRC_FILES})
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
