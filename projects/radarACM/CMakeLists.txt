# 1. Project Name
project(radarACM)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)
link_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 3. Project Build
file(GLOB_RECURSE SRC_LIST *.h *.cpp ../Common.h ../Common.cpp)
if(WIN32)
	get_imgui_src(${3RDPARTY_DIR}/include/imgui IMGUI_SRC_LIST)
endif()

if(ANDROID)
	add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME nb_jni_${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME} libnb rttr_core)
else()
	add_executable(${PROJECT_NAME} ${SRC_LIST} ${IMGUI_SRC_LIST})
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "../../../../dist/win32/lib")
if(WIN32)
	target_link_libraries(${PROJECT_NAME} libnb TCPConnect)
else()
	target_link_libraries(${PROJECT_NAME} libnb)
endif()
endif()


# 4. Project Install
if(ANDROID)
	install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
else()
	install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
if(WIN32)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/TCPConnect.dll DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
