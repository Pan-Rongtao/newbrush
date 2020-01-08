# 1. Project Name

project(lib)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)


# 4. Sub Projects

# 5. Project Install
if(MSVC)
	file(GLOB LIBS ${CMAKE_CURRENT_SOURCE_DIR}/*.dll ${CMAKE_CURRENT_SOURCE_DIR}/*.lib)
elseif(UNIX AND NOT ANDROID)
	file(GLOB LIBS linux-arm/release/*.so*)
endif()
	install(FILES ${LIBS} DESTINATION ${CMAKE_INSTALL_LIBDIR})
