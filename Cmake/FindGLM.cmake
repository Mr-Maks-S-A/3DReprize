set(GLM_SEARCH_PATHS    "${DEPENDENCIES_PATH}/glm"
                        ${glm_SOURCE_DIR}
                        ${CMAKE_INSTALL_INCLUDEDIR}
                        ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
                        )

find_path(GLM_INCLUDE_PATH
    NAMES glm/glm.hpp glm/gtx
    PATHS ${GLM_SEARCH_PATHS}
    PATH_SUFFIXES include
    )


if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
find_library(GLM_LIBRARIES_Debug
    NAMES libglm.a libglm.lib
    PATHS ${GLM_SEARCH_PATHS}
    PATH_SUFFIXES ${CMAKE_BUILD_TYPE}
    )
    SET(GLM_LIBRARIES ${GLM_LIBRARIES_Debug})
endif()


if(${CMAKE_BUILD_TYPE} STREQUAL Release)
find_library(GLM_LIBRARIES_Release
    NAMES libglm.a libglm.lib
    PATHS ${GLM_SEARCH_PATHS}
    PATH_SUFFIXES ${CMAKE_BUILD_TYPE}
    )
SET(GLM_LIBRARIES ${GLM_LIBRARIES_Release})
endif()


set(GLM_FOUND OFF)

if (GLM_INCLUDE_PATH AND GLM_LIBRARIES)
    set(GLM_FOUND ON)
    message(STATUS "SUCCESS: EXTERNAL LIBRARY 'GLM' FOUND")
    message(STATUS "GLM_INCLUDEPATH = ${GLM_INCLUDE_PATH}")
    message(STATUS "GLM_LIBRARIES = ${GLM_LIBRARIES}")
else ()
    message(STATUS "ERROR: EXTERNAL LIBRARY 'GLM' NOT FOUND")
endif (GLM_INCLUDE_PATH AND GLM_LIBRARIES)
