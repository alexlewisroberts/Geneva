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

# Utility rule file for testcode.

# Include the progress variables for this target.
include test/CMakeFiles/testcode.dir/progress.make

test/CMakeFiles/testcode:

testcode: test/CMakeFiles/testcode
testcode: test/CMakeFiles/testcode.dir/build.make
.PHONY : testcode

# Rule to build all files generated by this target.
test/CMakeFiles/testcode.dir/build: testcode
.PHONY : test/CMakeFiles/testcode.dir/build

test/CMakeFiles/testcode.dir/clean:
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/test && $(CMAKE_COMMAND) -P CMakeFiles/testcode.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/testcode.dir/clean

test/CMakeFiles/testcode.dir/depend:
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Hannes/Documents/Geneva/trunk /Users/Hannes/Documents/Geneva/trunk/test /Users/Hannes/Documents/Geneva/trunk/build/Unix /Users/Hannes/Documents/Geneva/trunk/build/Unix/test /Users/Hannes/Documents/Geneva/trunk/build/Unix/test/CMakeFiles/testcode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/testcode.dir/depend

