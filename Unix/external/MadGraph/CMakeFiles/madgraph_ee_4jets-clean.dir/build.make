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

# Utility rule file for madgraph_ee_4jets-clean.

# Include the progress variables for this target.
include external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/progress.make

external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean:
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Hannes/Documents/Geneva/trunk/build/Unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Performing clean step for 'madgraph_ee_4jets'"
	cd /Users/Hannes/Documents/Geneva/trunk/external/MadGraph/process_ee_4jets && make PROC=ee_4jets clean
	cd /Users/Hannes/Documents/Geneva/trunk/external/MadGraph/process_ee_4jets && /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/MadGraph/madgraph_ee_4jets-prefix/src/madgraph_ee_4jets-stamp/madgraph_ee_4jets-build

madgraph_ee_4jets-clean: external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean
madgraph_ee_4jets-clean: external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/build.make
.PHONY : madgraph_ee_4jets-clean

# Rule to build all files generated by this target.
external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/build: madgraph_ee_4jets-clean
.PHONY : external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/build

external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/clean:
.PHONY : external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/clean

external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/depend:
	cd /Users/Hannes/Documents/Geneva/trunk/build/Unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Hannes/Documents/Geneva/trunk /Users/Hannes/Documents/Geneva/trunk/external/MadGraph /Users/Hannes/Documents/Geneva/trunk/build/Unix /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/MadGraph /Users/Hannes/Documents/Geneva/trunk/build/Unix/external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/MadGraph/CMakeFiles/madgraph_ee_4jets-clean.dir/depend

