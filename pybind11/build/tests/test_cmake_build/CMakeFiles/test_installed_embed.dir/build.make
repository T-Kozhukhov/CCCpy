# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Coding/Libraries/pybind11-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Coding/Libraries/pybind11-master/build

# Utility rule file for test_installed_embed.

# Include the progress variables for this target.
include tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/progress.make

tests/test_cmake_build/CMakeFiles/test_installed_embed:
	cd /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build && /usr/bin/ctest --quiet --output-log installed_embed.log --build-and-test /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/installed_embed /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed --build-config Release --build-noclean --build-generator Unix\ Makefiles  --build-makeprogram /usr/bin/make --build-target check --build-options -DCMAKE_PREFIX_PATH=/mnt/d/Coding/Libraries/pybind11-master/build/mock_install -DCMAKE_CXX_COMPILER=/usr/bin/c++ -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python3.6 -DCMAKE_CXX_STANDARD=14 -DPYBIND11_CPP_STANDARD=

test_installed_embed: tests/test_cmake_build/CMakeFiles/test_installed_embed
test_installed_embed: tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/build.make

.PHONY : test_installed_embed

# Rule to build all files generated by this target.
tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/build: test_installed_embed

.PHONY : tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/build

tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/clean:
	cd /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build && $(CMAKE_COMMAND) -P CMakeFiles/test_installed_embed.dir/cmake_clean.cmake
.PHONY : tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/clean

tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/depend:
	cd /mnt/d/Coding/Libraries/pybind11-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Coding/Libraries/pybind11-master /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build /mnt/d/Coding/Libraries/pybind11-master/build /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/test_cmake_build/CMakeFiles/test_installed_embed.dir/depend

