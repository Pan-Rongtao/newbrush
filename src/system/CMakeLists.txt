
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(system)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)


# 3. Project Build

set(LIB_NAME "system")

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h" "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/topology/*.h" "*.h" "*.cpp" "topology/*.cpp")

add_library(${LIB_NAME} SHARED ${SRC_FILES})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME uit_nb-${LIB_NAME})
if(WIN32 AND NOT MINGW)
	target_link_libraries(${LIB_NAME} core)
elseif(UNIX AND NOT ANDROID)
	set(CMAKE_PREFIX_PATH   "$ENV{SDKTARGETSYSROOT}/usr/lib/cmake")
	include(FindPkgConfig)
	pkg_check_modules(WaylandEGL REQUIRED wayland-egl)
	target_link_libraries(${LIB_NAME} wayland-client ${WaylandEGL_LIBRARIES})
endif()

# 4. Project Install
if(WIN32)
	install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/debug CONFIGURATIONS debug)
	install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/release CONFIGURATIONS release)
elseif(UNIX AND NOT ANDROID)
	install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
