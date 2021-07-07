# 1. Project Name
project(unittests)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build
file(GLOB_RECURSE SRC_LIST *.h *.hpp *.cpp *.c)

add_executable(${PROJECT_NAME} ${SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "../../../dist/win32/lib")
target_link_libraries(${PROJECT_NAME} libnb)

# 4. Project Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
