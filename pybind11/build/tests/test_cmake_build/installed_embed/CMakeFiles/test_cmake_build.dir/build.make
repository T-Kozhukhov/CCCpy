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
CMAKE_SOURCE_DIR = /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/installed_embed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed

# Include any dependencies generated for this target.
include CMakeFiles/test_cmake_build.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_cmake_build.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_cmake_build.dir/flags.make

CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o: CMakeFiles/test_cmake_build.dir/flags.make
CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o: /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o -c /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp

CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp > CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.i

CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp -o CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.s

CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.requires:

.PHONY : CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.requires

CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.provides: CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_cmake_build.dir/build.make CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.provides.build
.PHONY : CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.provides

CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.provides.build: CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o


# Object files for target test_cmake_build
test_cmake_build_OBJECTS = \
"CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o"

# External object files for target test_cmake_build
test_cmake_build_EXTERNAL_OBJECTS =

test_cmake_build: CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o
test_cmake_build: CMakeFiles/test_cmake_build.dir/build.make
test_cmake_build: /usr/lib/x86_64-linux-gnu/libpython3.6m.so
test_cmake_build: CMakeFiles/test_cmake_build.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_cmake_build"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_cmake_build.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_cmake_build.dir/build: test_cmake_build

.PHONY : CMakeFiles/test_cmake_build.dir/build

CMakeFiles/test_cmake_build.dir/requires: CMakeFiles/test_cmake_build.dir/mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/embed.cpp.o.requires

.PHONY : CMakeFiles/test_cmake_build.dir/requires

CMakeFiles/test_cmake_build.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_cmake_build.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_cmake_build.dir/clean

CMakeFiles/test_cmake_build.dir/depend:
	cd /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/installed_embed /mnt/d/Coding/Libraries/pybind11-master/tests/test_cmake_build/installed_embed /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed /mnt/d/Coding/Libraries/pybind11-master/build/tests/test_cmake_build/installed_embed/CMakeFiles/test_cmake_build.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_cmake_build.dir/depend

