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
include src/CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/client.dir/flags.make

src/CMakeFiles/client.dir/client.c.o: src/CMakeFiles/client.dir/flags.make
src/CMakeFiles/client.dir/client.c.o: ../src/client.c
src/CMakeFiles/client.dir/client.c.o: src/CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/client.dir/client.c.o"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-2/src/client.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/client.dir/client.c.o -MF CMakeFiles/client.dir/client.c.o.d -o CMakeFiles/client.dir/client.c.o -c /home/raith/work/COMP-4981/Assignment-2/src/client.c

src/CMakeFiles/client.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/client.c.i"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-2/src/client.c > CMakeFiles/client.dir/client.c.i

src/CMakeFiles/client.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/client.c.s"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-2/src/client.c -o CMakeFiles/client.dir/client.c.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.c.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

src/client: src/CMakeFiles/client.dir/client.c.o
src/client: src/CMakeFiles/client.dir/build.make
src/client: /usr/lib/x86_64-linux-gnu/libm.so
src/client: /usr/local/lib/libdc_error.so
src/client: /usr/local/lib/libdc_posix.so
src/client: /usr/local/lib/libdc_util.so
src/client: /usr/local/lib/libdc_fsm.so
src/client: /usr/local/lib/libdc_application.so
src/client: /usr/local/lib/libdc_network.so
src/client: src/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable client"
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/client.dir/build: src/client
.PHONY : src/CMakeFiles/client.dir/build

src/CMakeFiles/client.dir/clean:
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/client.dir/clean

src/CMakeFiles/client.dir/depend:
	cd /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/raith/work/COMP-4981/Assignment-2 /home/raith/work/COMP-4981/Assignment-2/src /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src /home/raith/work/COMP-4981/Assignment-2/cmake-build-debug/src/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/client.dir/depend

