
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(gles)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build

set(LIB_NAME "gles")

set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/libnb/include/newbrush/rvl/${PROJECT_NAME})
file(GLOB_RECURSE INC_LIST ${INCLUDE_PREFIX}/*.h)
file(GLOB_RECURSE SRC_LIST *.cpp)

if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${INC_LIST})
	group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_LIST})
endif()

add_library(${LIB_NAME} SHARED ${INC_LIST} ${SRC_LIST})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME NbGles)

if(WIN32 AND NOT MINGW)
	target_link_libraries(${LIB_NAME} core libGLESv2 libEGL assimp-vc140-mtd)
elseif(UNIX AND NOT ANDROID)
	target_link_libraries(${LIB_NAME} core GLESv2 EGL)
endif()

# 4. Project Install
install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})