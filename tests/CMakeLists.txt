### This will be done only if unit testing is enabled, and done through the host's compiler, not the cross-compile one

if( (UNIT_TESTING) AND (UTESTS_BUILD STREQUAL "HOST") )

	###################### Google Test framework include ######################
	### This content gets fetched only once after doing the first "make setup xxx"
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG		release-1.11.0
	)

	message(STATUS "FETCHING GTest REPOSITORY CONTENT... --")
	FetchContent_MakeAvailable(googletest)
	message(STATUS "GTest CONTENT FETCHED SUCCESSFULLY! --")

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

	###################### ADD TEST DIRECTORIES ######################
	add_subdirectory(linked_list)


	###### TODO ----------------->>>>
	#if (ENABLE_COVERAGE)
	#    set(COVERAGE_MAIN "coverage")
	#    set(COVERAGE_EXCLUDES
	#        "${PROJECT_SOURCE_DIR}/cmake/*"
	#        "${PROJECT_SOURCE_DIR}/docs/*"
	#        "${PROJECT_SOURCE_DIR}/tests/*"
	#        "${PROJECT_SOURCE_DIR}/build/*"
	#        "${PROJECT_SOURCE_DIR}/config/*"
	#        "/usr/include/*"
	#		gtest_main
	#		)
	#
	#    #setup_target_for_coverage_lcov(
	#    #    NAME ${COVERAGE_MAIN}
	#    #    EXECUTABLE LinkedList_test
	#    #    DEPENDENCIES LinkedList_test
	#    #)
	#endif()

endif()