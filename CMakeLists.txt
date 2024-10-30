############################ PROJECT HEADER ############################
cmake_minimum_required(VERSION 3.19)

###### THIS NEEDS TO BE DONE ¡¡¡BEFORE!!! DEFINING -> project()
# Check if the TOOLCHAIN_SELECT variable is set
#if(TOOLCHAIN_SELECT)
#    # Determine which toolchain file to include based on the value of TOOLCHAIN_SELECT
#    if(TOOLCHAIN_SELECT STREQUAL "LinaroCrossArm64")
#        message(STATUS "Linaro Cross-compiler -- arm64 architecture -- SELECTED")
#        string(CONCAT CMAKE_TOOLCHAIN_FULL_PATH "${CMAKE_SOURCE_DIR}" "/cmake/linaroAarch64Toolchain.cmake")
#        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_TOOLCHAIN_FULL_PATH}" CACHE FILEPATH "Cross-compile toolchain path")
#    elseif(TOOLCHAIN_SELECT STREQUAL "OtherToolchain")
#        message(STATUS "OTHER TOOLCHAIN -- SELECTED")
#    endif()
#endif()

project(CMake-Template VERSION 1.0.0 LANGUAGES C CXX)

############################ PROJECT GLOBAL VARS ############################
### CMAKE-KCONFIG VARS ###
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
set(PROJECT_ROOT    ${CMAKE_SOURCE_DIR}/cmake-kconfig)
set(KCONFIG_ROOT    ${CMAKE_SOURCE_DIR}/config/Kconfig)
set(BOARD_DIR       ${CMAKE_SOURCE_DIR}/config/defconfigs)
set(AUTOCONF_H      ${CMAKE_SOURCE_DIR}/config/autoconf.h)
if(NOT DEFINED BOARD)
    set(BOARD dummy)
endif()

############################ PROJECT CONFIGURATION ############################
### THIS RECONFIGURES THE PROJECT IF CHANGE IN AUTOCONF IS DETECTED ###
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${AUTOCONF_H})

##### C/C++ flags #####
set(C_FLAGS  "")
set(C_ADDITIONAL_FLAGS  "")

if(EXTRA_WARNINGS)
    message(STATUS "EXTRA WARNINGS -- ENABLED!")
	set(C_ADDITIONAL_FLAGS  "${C_ADDITIONAL_FLAGS} -Wall -Wextra")
endif()
if(DEBUG_FLAG)
    message(STATUS "SETTING DEBUG FLAG:${DEBUG_FLAG}")
	set(C_ADDITIONAL_FLAGS  "${C_ADDITIONAL_FLAGS} ${DEBUG_FLAG}")
endif()
if(OPTIMIZATION_FLAG)
    message(STATUS "SETTING OPTIMIZATION FLAG:${OPTIMIZATION_FLAG}")
	set(C_ADDITIONAL_FLAGS  "${C_ADDITIONAL_FLAGS} ${OPTIMIZATION_FLAGS}")
endif()
if(UNIT_TESTING)
    enable_testing()
    message(STATUS "UNIT TESTING -- ENABLED!")
endif()
if(REGRESION_TESTING)
    message(STATUS "REGRESION TESTING -- ENABLED!")
endif()
if(PRINTF_DEBUG)
    message(STATUS "PRINTF DEBUGGING -- ENABLED!")
endif()

############################ PROJECT SUBDIRECTORIES AND INCLUDES ############################
### ADDS ALL CMAKE MODULES ###
include(cmake/top.cmake)

### INCLUDES DIRS THAT HAVE CMAKE FILES ###
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(config)