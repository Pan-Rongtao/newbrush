
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(media)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build

set(LIB_NAME "media")

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h" "*.h" "*.cpp")

add_library(${LIB_NAME} SHARED ${SRC_FILES})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME uit_nb-${LIB_NAME})
if(WIN32 AND NOT MINGW)
	target_link_libraries(${LIB_NAME} core system libexiv2 optimized FreeImage debug FreeImaged)
elseif(UNIX AND NOT ANDROID)
	target_link_libraries(${LIB_NAME} freeimage.a exiv2)
endif()

# 4. Project Install
if(WIN32)
	install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/debug CONFIGURATIONS debug)
	install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/release CONFIGURATIONS release)
elseif(UNIX AND NOT ANDROID)
	install(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
