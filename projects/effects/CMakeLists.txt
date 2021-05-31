# 1. Project Name
PROJECT(effects)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Project Build
file(GLOB_RECURSE SRC_LIST *.h *.cpp ../Common.h ../Common.cpp)

if(ANDROID)
	add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME nb_jni_${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME} libnb rttr_core)
else()
	add_executable(${PROJECT_NAME} ${SRC_LIST})
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME} libnb)
endif()


# 4. Project Install
IF(ANDROID)
	INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
ELSE()
	INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
ENDIF()
