cmake_minimum_required(VERSION 3.16)
project(DataStructures VERSION 1.0.0 LANGUAGES C CXX)

set(ENABLE_COVERAGE ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_KCONFIG_DIR ${CMAKE_SOURCE_DIR}/include/libs/cmake-kconfig)
set(KCONFIG_ROOT ${CMAKE_SOURCE_DIR}/config/Kconfig)
set(BOARD_DIR ${CMAKE_SOURCE_DIR}/config/defconfigs)
set(AUTOCONF_H ${CMAKE_SOURCE_DIR}/config/autoconf/autoconf.h)

# Re-configure (Re-execute all CMakeLists.txt code) when autoconf.h changes
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${AUTOCONF_H})

include(cmake/top.cmake)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(config)

if(CONFIG_TEST_OPTION)

    message("config test enabled!")

endif()