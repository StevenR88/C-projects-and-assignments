# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/raith/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/213.7172.20/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/raith/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/213.7172.20/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/raith/work/COMP-4981/Assignment-2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/logParser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/logParser.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/logParser.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/logParser.dir/flags.make

src/CMakeFiles/logParser.dir/logParser.c.o: src/CMakeFiles/logParser.dir/flags.make
src/CMakeFiles/logParser.dir/logParser.c.o: ../src/logParser.c
src/CMakeFiles/logParser.dir/logParser.c.o: src/CMakeFiles/logParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/logParser.dir/logParser.c.o"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-2/src/logParser.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/logParser.dir/logParser.c.o -MF CMakeFiles/logParser.dir/logParser.c.o.d -o CMakeFiles/logParser.dir/logParser.c.o -c /home/raith/work/COMP-4981/Assignment-2/src/logParser.c

src/CMakeFiles/logParser.dir/logParser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/logParser.dir/logParser.c.i"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-2/src/logParser.c > CMakeFiles/logParser.dir/logParser.c.i

src/CMakeFiles/logParser.dir/logParser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/logParser.dir/logParser.c.s"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-2/src/logParser.c -o CMakeFiles/logParser.dir/logParser.c.s

# Object files for target logParser
logParser_OBJECTS = \
"CMakeFiles/logParser.dir/logParser.c.o"

# External object files for target logParser
logParser_EXTERNAL_OBJECTS =

src/logParser: src/CMakeFiles/logParser.dir/logParser.c.o
src/logParser: src/CMakeFiles/logParser.dir/build.make
src/logParser: /usr/lib/x86_64-linux-gnu/libm.so
src/logParser: /usr/local/lib/libdc_error.so
src/logParser: /usr/local/lib/libdc_posix.so
src/logParser: /usr/local/lib/libdc_util.so
src/logParser: /usr/local/lib/libdc_fsm.so
src/logParser: /usr/local/lib/libdc_application.so
src/logParser: /usr/local/lib/libdc_network.so
src/logParser: src/CMakeFiles/logParser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable logParser"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logParser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/logParser.dir/build: src/logParser
.PHONY : src/CMakeFiles/logParser.dir/build

src/CMakeFiles/logParser.dir/clean:
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/logParser.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/logParser.dir/clean

src/CMakeFiles/logParser.dir/depend:
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/raith/work/COMP-4981/Assignment-2 /home/raith/work/COMP-4981/Assignment-2/src /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src/CMakeFiles/logParser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/logParser.dir/depend

