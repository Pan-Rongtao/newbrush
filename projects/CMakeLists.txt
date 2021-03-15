# 1. Project Name
project(projects)

# 2. Platform Env (Include/Lib Path, C/CXX/LD FLAGS)

# 3. Sub Projects
IF(WIN32)
add_subdirectory(player)
add_subdirectory(radarACM)
add_subdirectory(effects)
SET_PROPERTY(TARGET player PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET radarACM PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET effects PROPERTY FOLDER ${PROJECT_NAME})
ENDIF()
add_subdirectory(cx62b)
add_subdirectory(cdx706)
SET_PROPERTY(TARGET cx62b PROPERTY FOLDER ${PROJECT_NAME})
SET_PROPERTY(TARGET cdx706 PROPERTY FOLDER ${PROJECT_NAME})

add_subdirectory(browser)
SET_PROPERTY(TARGET browser PROPERTY FOLDER ${PROJECT_NAME})

# 5. Project Install
