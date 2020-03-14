
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

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/include/newbrush/${PROJECT_NAME}/*.h" "*.h" "*.cpp")

add_library(${LIB_NAME} SHARED ${SRC_FILES})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME NbGles)
if(WIN32 AND NOT MINGW)
	target_link_libraries(${LIB_NAME} core media libGLESv2 libEGL freetype assimp)
elseif(UNIX AND NOT ANDROID)
	target_link_libraries(${LIB_NAME} core media GLESv2 EGL freetype)
endif()

# 4. Project Install
install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})