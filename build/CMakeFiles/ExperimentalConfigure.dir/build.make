# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/lorenzo17/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/lorenzo17/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lorenzo17/Roundabout2/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lorenzo17/Roundabout2/build

# Utility rule file for ExperimentalConfigure.

# Include any custom commands dependencies for this target.
include CMakeFiles/ExperimentalConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ExperimentalConfigure.dir/progress.make

CMakeFiles/ExperimentalConfigure:
	/home/lorenzo17/.local/lib/python3.8/site-packages/cmake/data/bin/ctest -D ExperimentalConfigure

ExperimentalConfigure: CMakeFiles/ExperimentalConfigure
ExperimentalConfigure: CMakeFiles/ExperimentalConfigure.dir/build.make
.PHONY : ExperimentalConfigure

# Rule to build all files generated by this target.
CMakeFiles/ExperimentalConfigure.dir/build: ExperimentalConfigure
.PHONY : CMakeFiles/ExperimentalConfigure.dir/build

CMakeFiles/ExperimentalConfigure.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExperimentalConfigure.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExperimentalConfigure.dir/clean

CMakeFiles/ExperimentalConfigure.dir/depend:
	cd /home/lorenzo17/Roundabout2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lorenzo17/Roundabout2/source /home/lorenzo17/Roundabout2/source /home/lorenzo17/Roundabout2/build /home/lorenzo17/Roundabout2/build /home/lorenzo17/Roundabout2/build/CMakeFiles/ExperimentalConfigure.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ExperimentalConfigure.dir/depend

