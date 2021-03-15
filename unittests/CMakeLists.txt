# 1. Project Name
project(unittests)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build
set(BIN_NAME "unittests")

set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/unittests)
file(GLOB_RECURSE INC_LIST ${INCLUDE_PREFIX}/*.h ${INCLUDE_PREFIX}/*.hpp)
file(GLOB_RECURSE SRC_LIST *.cpp *.c)
if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${INC_LIST})
	group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_LIST})
endif()

add_executable(${BIN_NAME} ${INC_LIST} ${SRC_LIST})
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME ${BIN_NAME})
target_link_libraries(${BIN_NAME} libnb)

# 4. Project Install
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
