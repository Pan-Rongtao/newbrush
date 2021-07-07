# 1. Project Name
PROJECT(libnb)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build
SET(LIB_NAME "libnb")

set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/libnb/newbrush)
file(GLOB_RECURSE INC_LIST *.h *.hpp) 
file(GLOB_RECURSE SRC_LIST *.cpp *.c)
file(GLOB_RECURSE SHADER_LIST shader/*.vs shader/*.fs)
set(SRC_LIST ${SRC_LIST} ${3RDPARTY_DIR}/include/glad/glad.c ${3RDPARTY_DIR}/include/clipper/clipper.cpp ${3RDPARTY_DIR}/include/simdjson/simdjson.cpp)
if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${SHADER_LIST})
endif()

if(WIN32)
	add_library(${LIB_NAME} STATIC ${INC_LIST} ${SRC_LIST} ${SHADER_LIST})
else()
	add_library(${LIB_NAME} SHARED ${INC_LIST} ${SRC_LIST} ${SHADER_LIST})
endif()
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME nb)

if("${TARGET}" MATCHES "win")
	target_link_libraries(${LIB_NAME} glfw3 optimized assimp-vc140-mt debug assimp-vc140-mtd optimized rttr_core debug rttr_core_d)
elseif("${TARGET}" STREQUAL "linux64")
	target_link_libraries(${LIB_NAME} glfw3 X11 pthread rttr_core assimp)
elseif("${TARGET}" STREQUAL "android")
	target_link_libraries(${LIB_NAME} rttr_core assimp log android GLESv3)
elseif("${TARGET}" MATCHES "qnx")
	target_link_libraries(${LIB_NAME} rttr_core assimp screen GLESv2 EGL)
endif()

# 4. Project Install
INSTALL(TARGETS ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
FILE(GLOB INCLUDES *.h *.hpp)
INSTALL(FILES ${INCLUDES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/newbrush)
