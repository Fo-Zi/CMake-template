include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG		release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(
	GTest::GTest 
	INTERFACE 
	IMPORTED
)

target_link_libraries(
	GTest::GTest 
	INTERFACE 
	gtest_main
)

add_executable(
	LinkedList_test 
	linked_list_test.cpp 
	main.cpp
)

target_link_libraries(
	LinkedList_test
	PRIVATE
	gtest_main	
	LinkedList
)

add_test(LinkedList_gtest LinkedList_test)

if (ENABLE_COVERAGE)
    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
        "${PROJECT_SOURCE_DIR}/cmake/*"
        "${PROJECT_SOURCE_DIR}/docs/*"
        "${PROJECT_SOURCE_DIR}/tests/*"
        "${PROJECT_SOURCE_DIR}/build/*"
        "${PROJECT_SOURCE_DIR}/config/*"
        "/usr/include/*"
		gtest_main
		)

    setup_target_for_coverage_lcov(
        NAME ${COVERAGE_MAIN}
        EXECUTABLE LinkedList_test
        DEPENDENCIES LinkedList_test
    )
endif()