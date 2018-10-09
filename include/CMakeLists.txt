# 1. Project Name

project(include)

# 2. Platform Env (Include/Lib Path, C/CXX/LD FLAGS)



# 3. Sub Projects


# 5. Project Install
install(DIRECTORY core DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/newbrush)
install(DIRECTORY system DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/newbrush)
install(DIRECTORY media DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/newbrush)
install(DIRECTORY gles DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/newbrush)
install(DIRECTORY gui DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/newbrush)
