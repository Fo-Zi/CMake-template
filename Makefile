## GLOBAL VARIABLES ##
CURRENT_DIR := $(shell pwd)

BROWSER=google-chrome
DOXY_HTML_PATH=docs/html
DOXYGEN=/usr/bin/doxygen 
DOXYGEN_CONFIG=docs/Doxyfile

# --------------- COMMANDS --------------- #
setup:
	mkdir -p build_host 
	mkdir -p build_target 
	mkdir -p executables 
	cd build_host && cmake --preset="$(filter-out $@,$(MAKECMDGOALS))" -DUTESTS_BUILD="HOST" ..
	cd build_target && cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/linaroAarch64Toolchain.cmake --preset="$(filter-out $@,$(MAKECMDGOALS))" ..

menuconfig:
	cd build && make menuconfig 
	
compile:	
	cmake --build build

run_tests:
	cd build_host && make && ctest -VV

clean:
	rm -rf build_host && rm -rf build_target && rm -rf executables && rm -rf docs/html

install_cov:
	sudo apt-get install gcovr lcov
	
install_docs:
	pip install jinja2 Pygments
	sudo apt-get install doxygen
	sudo apt-get install graphviz

generate_docs:
	cmake --build ./build --target Docs
	
open_docs:
	${BROWSER} ${DOXY_HTML_PATH}/index.html
	
# Path to executable must include the inner folders too: example -> tests/on_target/WEB_SERVER_1
#
# NOTE: the cross-compile toolchain is "old", so some libraries it needs for debugging may not be on the system you're
# trying to execute this command. If that's the case, check for the error output and install them.
cgdb_launch:
	gnome-terminal -- bash -c "cgdb -d $(TOOLCHAIN_BIN_PATH)/aarch64-linux-gnu-gdb -- -ex 'file $(CURRENT_DIR)/executables/$(EXECUTABLE)' -ex 'set directories $(CURRENT_DIR)/src/modules'"
	
	

