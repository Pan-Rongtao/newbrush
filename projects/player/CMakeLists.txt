# 1. Project Name
project(player)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)
include_directories(rcf/include)
add_definitions("-DWIN32_LEAN_AND_MEAN")
add_definitions("-D_WIN32_WINNT=0x0601")

# 3. Project Build
set(BIN_NAME "player")

set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/projects/player)
file(GLOB_RECURSE INC_LIST ${INCLUDE_PREFIX}/*.h ${INCLUDE_PREFIX}/*.hpp)
file(GLOB_RECURSE SRC_LIST *.cpp *.c)

set(FILETER_SRC_LIST "")
FOREACH(src ${INC_LIST} ${SRC_LIST})
    IF(NOT (src MATCHES "rcf") OR src MATCHES "RCF.cpp")
		set(FILETER_SRC_LIST ${FILETER_SRC_LIST} ${src})
	ENDIF() 
ENDFOREACH()

if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${FILETER_SRC_LIST})
endif()

add_executable(${BIN_NAME}  ${FILETER_SRC_LIST})
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME ${BIN_NAME})
target_link_libraries(${BIN_NAME} libnb ws2_32)

# 4. Project Install
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
INSTALL(TARGETS ${BIN_NAME} DESTINATION D:/github/studio/dist/win32/lib)
