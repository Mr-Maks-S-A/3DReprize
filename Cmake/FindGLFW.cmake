set(GLFW_SEARCH_PATHS   "${DEPENDENCIES_PATH}/glfw/include"
                        ${glfw_SOURCE_DIR}
                        ${CMAKE_INSTALL_INCLUDEDIR}
                        ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
                        )

find_path(GLFW_INCLUDE_PATH
    NAMES GLFW/glfw3.h
    HINTS "${GLFW_LOCATION}/include"
          "$ENV{GLFW_LOCATION}/include"
    PATHS ${GLM_SEARCH_PATHS}
    PATH_SUFFIXES include
    )

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
find_library(GLFW_LIBRARIES_Debug
    NAMES  glfw.a glfw.lib
           glfw3.a glfw3.lib
    PATHS ${GLFW_SEARCH_PATHS}
    PATH_SUFFIXES ${CMAKE_BUILD_TYPE}
    )
    SET(GLFW_LIBRARIES ${GLFW_LIBRARIES_Debug})
endif()


if(${CMAKE_BUILD_TYPE} STREQUAL Release)
find_library(GLFW_LIBRARIES_Release
    NAMES libglm.a libglm.lib
    PATHS ${GLFW_SEARCH_PATHS}
    PATH_SUFFIXES ${CMAKE_BUILD_TYPE}
    )
SET(GLM_LIBRARIES ${GLFW_LIBRARIES_Release})
endif()




SET(GLFW_FOUND OFF)

if (GLFW_INCLUDE_PATH AND GLFW_LIBRARIES)
    SET(GLFW_FOUND ON)
    message(STATUS "SUCCESS: EXTERNAL LIBRARY 'GLFW' FOUND")
    message(STATUS "GLFW_INCLUDEPATH = ${GLFW_INCLUDE_PATH}")
    message(STATUS "GLFW_LIBRARIES = ${GLFW_LIBRARIES}")
else ()
    message(STATUS "ERROR: EXTERNAL LIBRARY 'GLFW' NOT FOUND")
endif (GLFW_INCLUDE_PATH AND GLFW_LIBRARIES)