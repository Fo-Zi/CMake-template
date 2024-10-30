################ LINKED LIST TEST EXAMPLE ################

### -LinkedList_test is the name of the executable-test.
### -It needs a reference to both the .cpp tests and the main test runner
add_executable(
	LinkedList_test 
	./linked_list_test.cpp 
	./../main.cpp
)

### -This allows you to simply do: #include <LinkedList.h> instead of having to pass the absolute
### path like: #include "./../../include/LinkedList.h" 
target_include_directories(LinkedList_test PRIVATE 
	${CMAKE_SOURCE_DIR}/include
)

### -Both header and source are needed here. This is what the compiler will link together .h and .c 
### with the test executable to create an .o
### -You can replace the implementation(.c) easily by specifying which source to use.
target_sources(LinkedList_test PRIVATE 
	${CMAKE_SOURCE_DIR}/include/LinkedList.h
	${CMAKE_SOURCE_DIR}/src/LinkedList.c
)

### You link against the gtest_main to use GTest capabilities. This was defined upper in the CMakeLists.txt hierarchy
target_link_libraries(
	LinkedList_test
	PRIVATE
	gtest_main	
	pthread
)

### Adds the test
add_test(LinkedList_gtest LinkedList_test)