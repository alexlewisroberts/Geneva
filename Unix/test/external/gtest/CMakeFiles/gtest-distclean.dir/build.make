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

# Utility rule file for gtest-distclean.

# Include the progress variables for this target.
include external/gtest/CMakeFiles/gtest-distclean.dir/progress.make

external/gtest/CMakeFiles/gtest-distclean:
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hannes/Documents/Geneva/trunk/build/Unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Performing distclean step for 'gtest'"
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove_directory /Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove_directory /Users/Hannes/Documents/Geneva/trunk/external/gtest/gtest-1.6.0
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/gtest-prefix/src/gtest-stamp/gtest-mkdir
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/gtest-prefix/src/gtest-stamp/gtest-download
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/gtest-prefix/src/gtest-stamp/gtest-update
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/gtest-prefix/src/gtest-stamp/gtest-patch
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/gtest-prefix/src/gtest-stamp/gtest-configure
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/gtest-prefix/src/gtest-stamp/gtest-build

gtest-distclean: external/gtest/CMakeFiles/gtest-distclean
gtest-distclean: external/gtest/CMakeFiles/gtest-distclean.dir/build.make
.PHONY : gtest-distclean

# Rule to build all files generated by this target.
external/gtest/CMakeFiles/gtest-distclean.dir/build: gtest-distclean
.PHONY : external/gtest/CMakeFiles/gtest-distclean.dir/build

external/gtest/CMakeFiles/gtest-distclean.dir/clean:
.PHONY : external/gtest/CMakeFiles/gtest-distclean.dir/clean

external/gtest/CMakeFiles/gtest-distclean.dir/depend:
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Hannes/Documents/Geneva/trunk /Users/Hannes/Documents/Geneva/trunk/external/gtest /Users/Hannes/Documents/Geneva/trunk/build/Unix /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/gtest/CMakeFiles/gtest-distclean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/gtest/CMakeFiles/gtest-distclean.dir/depend

