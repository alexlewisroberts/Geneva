# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.12/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.12/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Hannes/Documents/Geneva/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Hannes/Documents/Geneva/trunk/build/Unix

# Include any dependencies generated for this target.
include test/utils/CMakeFiles/TestUtils.dir/depend.make

# Include the progress variables for this target.
include test/utils/CMakeFiles/TestUtils.dir/progress.make

# Include the compile flags for this target's objects.
include test/utils/CMakeFiles/TestUtils.dir/flags.make

test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o: test/utils/CMakeFiles/TestUtils.dir/flags.make
test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o: ../../test/utils/TestDataReader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hannes/Documents/Geneva/trunk/build/Unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestUtils.dir/TestDataReader.cpp.o -c /Users/Hannes/Documents/Geneva/trunk/test/utils/TestDataReader.cpp

test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestUtils.dir/TestDataReader.cpp.i"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hannes/Documents/Geneva/trunk/test/utils/TestDataReader.cpp > CMakeFiles/TestUtils.dir/TestDataReader.cpp.i

test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestUtils.dir/TestDataReader.cpp.s"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hannes/Documents/Geneva/trunk/test/utils/TestDataReader.cpp -o CMakeFiles/TestUtils.dir/TestDataReader.cpp.s

test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.requires:
.PHONY : test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.requires

test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.provides: test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.requires
	$(MAKE) -f test/utils/CMakeFiles/TestUtils.dir/build.make test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.provides.build
.PHONY : test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.provides

test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.provides.build: test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o

test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o: test/utils/CMakeFiles/TestUtils.dir/flags.make
test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o: ../../test/utils/TestUtils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hannes/Documents/Geneva/trunk/build/Unix/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestUtils.dir/TestUtils.cpp.o -c /Users/Hannes/Documents/Geneva/trunk/test/utils/TestUtils.cpp

test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestUtils.dir/TestUtils.cpp.i"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hannes/Documents/Geneva/trunk/test/utils/TestUtils.cpp > CMakeFiles/TestUtils.dir/TestUtils.cpp.i

test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestUtils.dir/TestUtils.cpp.s"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hannes/Documents/Geneva/trunk/test/utils/TestUtils.cpp -o CMakeFiles/TestUtils.dir/TestUtils.cpp.s

test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.requires:
.PHONY : test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.requires

test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.provides: test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.requires
	$(MAKE) -f test/utils/CMakeFiles/TestUtils.dir/build.make test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.provides.build
.PHONY : test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.provides

test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.provides.build: test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o

test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o: test/utils/CMakeFiles/TestUtils.dir/flags.make
test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o: ../../test/utils/InputGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hannes/Documents/Geneva/trunk/build/Unix/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestUtils.dir/InputGenerator.cpp.o -c /Users/Hannes/Documents/Geneva/trunk/test/utils/InputGenerator.cpp

test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestUtils.dir/InputGenerator.cpp.i"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hannes/Documents/Geneva/trunk/test/utils/InputGenerator.cpp > CMakeFiles/TestUtils.dir/InputGenerator.cpp.i

test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestUtils.dir/InputGenerator.cpp.s"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hannes/Documents/Geneva/trunk/test/utils/InputGenerator.cpp -o CMakeFiles/TestUtils.dir/InputGenerator.cpp.s

test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.requires:
.PHONY : test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.requires

test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.provides: test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.requires
	$(MAKE) -f test/utils/CMakeFiles/TestUtils.dir/build.make test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.provides.build
.PHONY : test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.provides

test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.provides.build: test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o

test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o: test/utils/CMakeFiles/TestUtils.dir/flags.make
test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o: ../../test/utils/ConfigurationBank.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hannes/Documents/Geneva/trunk/build/Unix/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o -c /Users/Hannes/Documents/Geneva/trunk/test/utils/ConfigurationBank.cpp

test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.i"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Hannes/Documents/Geneva/trunk/test/utils/ConfigurationBank.cpp > CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.i

test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.s"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Hannes/Documents/Geneva/trunk/test/utils/ConfigurationBank.cpp -o CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.s

test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.requires:
.PHONY : test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.requires

test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.provides: test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.requires
	$(MAKE) -f test/utils/CMakeFiles/TestUtils.dir/build.make test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.provides.build
.PHONY : test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.provides

test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.provides.build: test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o

# Object files for target TestUtils
TestUtils_OBJECTS = \
"CMakeFiles/TestUtils.dir/TestDataReader.cpp.o" \
"CMakeFiles/TestUtils.dir/TestUtils.cpp.o" \
"CMakeFiles/TestUtils.dir/InputGenerator.cpp.o" \
"CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o"

# External object files for target TestUtils
TestUtils_EXTERNAL_OBJECTS =

../../lib/libTestUtils.a: test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o
../../lib/libTestUtils.a: test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o
../../lib/libTestUtils.a: test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o
../../lib/libTestUtils.a: test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o
../../lib/libTestUtils.a: test/utils/CMakeFiles/TestUtils.dir/build.make
../../lib/libTestUtils.a: test/utils/CMakeFiles/TestUtils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../../../lib/libTestUtils.a"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && $(CMAKE_COMMAND) -P CMakeFiles/TestUtils.dir/cmake_clean_target.cmake
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestUtils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/utils/CMakeFiles/TestUtils.dir/build: ../../lib/libTestUtils.a
.PHONY : test/utils/CMakeFiles/TestUtils.dir/build

test/utils/CMakeFiles/TestUtils.dir/requires: test/utils/CMakeFiles/TestUtils.dir/TestDataReader.cpp.o.requires
test/utils/CMakeFiles/TestUtils.dir/requires: test/utils/CMakeFiles/TestUtils.dir/TestUtils.cpp.o.requires
test/utils/CMakeFiles/TestUtils.dir/requires: test/utils/CMakeFiles/TestUtils.dir/InputGenerator.cpp.o.requires
test/utils/CMakeFiles/TestUtils.dir/requires: test/utils/CMakeFiles/TestUtils.dir/ConfigurationBank.cpp.o.requires
.PHONY : test/utils/CMakeFiles/TestUtils.dir/requires

test/utils/CMakeFiles/TestUtils.dir/clean:
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils && $(CMAKE_COMMAND) -P CMakeFiles/TestUtils.dir/cmake_clean.cmake
.PHONY : test/utils/CMakeFiles/TestUtils.dir/clean

test/utils/CMakeFiles/TestUtils.dir/depend:
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Hannes/Documents/Geneva/trunk /Users/Hannes/Documents/Geneva/trunk/test/utils /Users/Hannes/Documents/Geneva/trunk/build/Unix /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/utils/CMakeFiles/TestUtils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/utils/CMakeFiles/TestUtils.dir/depend

