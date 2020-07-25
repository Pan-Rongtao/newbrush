
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(core)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)


# 3. Project Build

set(LIB_NAME "core")

set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/libnb/include/newbrush/${PROJECT_NAME})
file(GLOB_RECURSE INC_LIST ${INCLUDE_PREFIX}/*.h)
file(GLOB_RECURSE SRC_LIST *.cpp)

if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${INC_LIST})
	group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_LIST})
endif()

add_library(${LIB_NAME} SHARED ${INC_LIST} ${SRC_LIST})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME NbCore)

if(WIN32 AND NOT MINGW)
	target_link_libraries(${LIB_NAME} rttr_core_d freetype openGL32 SOIL)
elseif(UNIX AND NOT ANDROID)
	set(CMAKE_PREFIX_PATH   "$ENV{SDKTARGETSYSROOT}/usr/lib/cmake")
	include(FindPkgConfig)
	pkg_check_modules(WaylandEGL REQUIRED wayland-egl)
	target_link_libraries(${LIB_NAME} wayland-client ${WaylandEGL_LIBRARIES})
endif()

# 4. Project Install
install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})