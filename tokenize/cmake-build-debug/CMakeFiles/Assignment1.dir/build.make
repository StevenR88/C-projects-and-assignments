# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = "/cygdrive/c/Users/Steven Reid/AppData/Local/JetBrains/CLion2022.1/cygwin_cmake/bin/cmake.exe"

# The command to remove a file.
RM = "/cygdrive/c/Users/Steven Reid/AppData/Local/JetBrains/CLion2022.1/cygwin_cmake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Assignment1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Assignment1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Assignment1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assignment1.dir/flags.make

CMakeFiles/Assignment1.dir/main.c.o: CMakeFiles/Assignment1.dir/flags.make
CMakeFiles/Assignment1.dir/main.c.o: ../main.c
CMakeFiles/Assignment1.dir/main.c.o: CMakeFiles/Assignment1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Assignment1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Assignment1.dir/main.c.o -MF CMakeFiles/Assignment1.dir/main.c.o.d -o CMakeFiles/Assignment1.dir/main.c.o -c /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/main.c

CMakeFiles/Assignment1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Assignment1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/main.c > CMakeFiles/Assignment1.dir/main.c.i

CMakeFiles/Assignment1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Assignment1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/main.c -o CMakeFiles/Assignment1.dir/main.c.s

# Object files for target Assignment1
Assignment1_OBJECTS = \
"CMakeFiles/Assignment1.dir/main.c.o"

# External object files for target Assignment1
Assignment1_EXTERNAL_OBJECTS =

Assignment1.exe: CMakeFiles/Assignment1.dir/main.c.o
Assignment1.exe: CMakeFiles/Assignment1.dir/build.make
Assignment1.exe: CMakeFiles/Assignment1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Assignment1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assignment1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assignment1.dir/build: Assignment1.exe
.PHONY : CMakeFiles/Assignment1.dir/build

CMakeFiles/Assignment1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Assignment1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Assignment1.dir/clean

CMakeFiles/Assignment1.dir/depend:
	cd /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1 /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1 /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug /cygdrive/c/CLionWorkspace/COMP2510/COMP2510Assignment1/cmake-build-debug/CMakeFiles/Assignment1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Assignment1.dir/depend

