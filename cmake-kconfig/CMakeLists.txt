cmake_minimum_required(VERSION 3.13)

# Disable CMake printing from the current directory down
set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")

project(kconfig-test
    VERSION     1.0
    DESCRIPTION "kconfig test project"
    LANGUAGES   C
)

include(cmake/top.cmake)

if(CONFIG_TEST_OPTION)

    message("Config test_option enabled")

endif()