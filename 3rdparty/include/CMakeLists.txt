# 1. Project Name

project(include)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)


# 4. Sub Projects

# 5. Project Install
if(MSVC)
	install(DIRECTORY glm DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()