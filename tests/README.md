## Tests
### Recommended approach
The recommendation is to have each module's tests in their own folder, so you don't end up with +30 files all scattered in a single folder. Then you can add the tests as described in the following section.

### Adding new tests
Note that there's only one main "main.cpp" which in two lines runs all "registered tests".
To register tests you must add an executable with your test source (example: linked_list_test.cpp), give it a meaningful name, and include within the executable the main.cpp. Example:
```
add_executable(
	LinkedList_test 
	./linked_list_test.cpp 
	./../main.cpp
)
```
Then you add the sources of that particular test:
```
target_sources(LinkedList_test PRIVATE 
	${CMAKE_SOURCE_DIR}/include/LinkedList.h
	${CMAKE_SOURCE_DIR}/src/LinkedList.c
)
```
You then link it with the GTest library:
```
target_link_libraries(
	LinkedList_test
	PRIVATE
	gtest_main	
)
```
And finally add the test:
```
add_test(LinkedList_gtest LinkedList_test)
```

Note that while this may seem tedious, the 'test' actually contains +20 test cases inside. You would most likely add one of these tests by module and not by source.

### Mocking and hardware dependencies
Many time you're developing embedded software, you don't have the hardware available, or you have a HW dependency that doesn't allow you to automate the testing. But by having te header (interface) and the source separated
you can provide a dummy .c file, and use it as source file instead of the actual hw dependant one. You could easily do:
```
target_sources(LinkedList_test PRIVATE 
	${CMAKE_SOURCE_DIR}/include/LinkedList.h
	./LinkedList_dummy.c
)
```
And then emulate the functionalities you need. If you for example have a SensorInterface that has a read_temperature() method, you can use in dummy a pseudo-random generator, or a table with data, and feed that data to
the test, emulating the actual behavior of the sensor.
