# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2021.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2021.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\code\c++\B+

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\code\c++\B+\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/B_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/B_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/B_.dir/flags.make

CMakeFiles/B_.dir/main.cpp.obj: CMakeFiles/B_.dir/flags.make
CMakeFiles/B_.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\code\c++\B+\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/B_.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\B_.dir\main.cpp.obj -c E:\code\c++\B+\main.cpp

CMakeFiles/B_.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/B_.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\code\c++\B+\main.cpp > CMakeFiles\B_.dir\main.cpp.i

CMakeFiles/B_.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/B_.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\code\c++\B+\main.cpp -o CMakeFiles\B_.dir\main.cpp.s

# Object files for target B_
B__OBJECTS = \
"CMakeFiles/B_.dir/main.cpp.obj"

# External object files for target B_
B__EXTERNAL_OBJECTS =

B_.exe: CMakeFiles/B_.dir/main.cpp.obj
B_.exe: CMakeFiles/B_.dir/build.make
B_.exe: CMakeFiles/B_.dir/linklibs.rsp
B_.exe: CMakeFiles/B_.dir/objects1.rsp
B_.exe: CMakeFiles/B_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\code\c++\B+\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable B_.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\B_.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/B_.dir/build: B_.exe

.PHONY : CMakeFiles/B_.dir/build

CMakeFiles/B_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\B_.dir\cmake_clean.cmake
.PHONY : CMakeFiles/B_.dir/clean

CMakeFiles/B_.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\code\c++\B+ E:\code\c++\B+ E:\code\c++\B+\cmake-build-debug E:\code\c++\B+\cmake-build-debug E:\code\c++\B+\cmake-build-debug\CMakeFiles\B_.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/B_.dir/depend
