# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/145/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/145/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joeltanig77/CLionProjects/RadixTrees

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RadixTrees.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RadixTrees.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RadixTrees.dir/flags.make

CMakeFiles/RadixTrees.dir/main.c.o: CMakeFiles/RadixTrees.dir/flags.make
CMakeFiles/RadixTrees.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RadixTrees.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RadixTrees.dir/main.c.o   -c /home/joeltanig77/CLionProjects/RadixTrees/main.c

CMakeFiles/RadixTrees.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RadixTrees.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/joeltanig77/CLionProjects/RadixTrees/main.c > CMakeFiles/RadixTrees.dir/main.c.i

CMakeFiles/RadixTrees.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RadixTrees.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/joeltanig77/CLionProjects/RadixTrees/main.c -o CMakeFiles/RadixTrees.dir/main.c.s

CMakeFiles/RadixTrees.dir/radixFunc.c.o: CMakeFiles/RadixTrees.dir/flags.make
CMakeFiles/RadixTrees.dir/radixFunc.c.o: ../radixFunc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/RadixTrees.dir/radixFunc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RadixTrees.dir/radixFunc.c.o   -c /home/joeltanig77/CLionProjects/RadixTrees/radixFunc.c

CMakeFiles/RadixTrees.dir/radixFunc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RadixTrees.dir/radixFunc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/joeltanig77/CLionProjects/RadixTrees/radixFunc.c > CMakeFiles/RadixTrees.dir/radixFunc.c.i

CMakeFiles/RadixTrees.dir/radixFunc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RadixTrees.dir/radixFunc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/joeltanig77/CLionProjects/RadixTrees/radixFunc.c -o CMakeFiles/RadixTrees.dir/radixFunc.c.s

# Object files for target RadixTrees
RadixTrees_OBJECTS = \
"CMakeFiles/RadixTrees.dir/main.c.o" \
"CMakeFiles/RadixTrees.dir/radixFunc.c.o"

# External object files for target RadixTrees
RadixTrees_EXTERNAL_OBJECTS =

RadixTrees: CMakeFiles/RadixTrees.dir/main.c.o
RadixTrees: CMakeFiles/RadixTrees.dir/radixFunc.c.o
RadixTrees: CMakeFiles/RadixTrees.dir/build.make
RadixTrees: CMakeFiles/RadixTrees.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable RadixTrees"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RadixTrees.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RadixTrees.dir/build: RadixTrees

.PHONY : CMakeFiles/RadixTrees.dir/build

CMakeFiles/RadixTrees.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RadixTrees.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RadixTrees.dir/clean

CMakeFiles/RadixTrees.dir/depend:
	cd /home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joeltanig77/CLionProjects/RadixTrees /home/joeltanig77/CLionProjects/RadixTrees /home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug /home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug /home/joeltanig77/CLionProjects/RadixTrees/cmake-build-debug/CMakeFiles/RadixTrees.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RadixTrees.dir/depend

