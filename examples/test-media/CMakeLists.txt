
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(test-media)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build

set(BIN_NAME "test-media")

file(GLOB SRC_FILES "*.h" "*.cpp")

add_executable(${BIN_NAME} ${SRC_FILES})
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME nb.test.${BIN_NAME})
target_link_libraries(${BIN_NAME} core media gles gui)

# 4. Project Install
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
