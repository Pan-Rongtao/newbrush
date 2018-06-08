
####################################################################################################

# Company       : Huizhou Desay SV Automotive Co., Ltd.

# Division      : Automotive Electronics, Desay Corporation

# Business Unit : Central Technology

# Department    : Advanced Development (Huizhou)

####################################################################################################

# 1. Project Name

project(testmedia)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build

set(BIN_NAME "testmedia")

file(GLOB SRC_FILES "*.h" "*.cpp")

add_executable(${BIN_NAME} ${SRC_FILES})
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME uit.nb.test.${BIN_NAME})
target_link_libraries(${BIN_NAME} core system math media network gles gui)

# 4. Project Install
if(WIN32)
	install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR}/debug CONFIGURATIONS debug)
	install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR}/release CONFIGURATIONS release)
elseif(UNIX AND NOT ANDROID)
	install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
