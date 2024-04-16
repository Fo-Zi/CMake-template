
# Re-configure (Re-execute all CMakeLists.txt code) when autoconf.h changes
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${AUTOCONF_H})

include(cmake/AddGitSubmodule.cmake)
include(cmake/CodeCoverage.cmake)
include(cmake/Docs.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/include/libs/cmake-kconfig)
