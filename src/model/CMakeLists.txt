
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(model)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)


# 3. Project Build

set(LIB_NAME "model")

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/include/newbrush/${PROJECT_NAME}/*.h" "*.h" "*.cpp" "${CMAKE_SOURCE_DIR}/include/newbrush/${PROJECT_NAME}/../*.h" )
add_library(${LIB_NAME} SHARED ${SRC_FILES})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME model)
if(WIN32 AND NOT MINGW)
	target_link_libraries(${LIB_NAME} libGLESv2 libEGL assimp-vc140-mtd rttr_core_d)
elseif(UNIX AND NOT ANDROID)
	target_link_libraries(${LIB_NAME} GLESv2 EGL)
endif()

# 4. Project Install
install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})