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
CMAKE_SOURCE_DIR = /home/raith/work/COMP-4981/Assignment-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/dc_shell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/dc_shell.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/dc_shell.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/dc_shell.dir/flags.make

src/CMakeFiles/dc_shell.dir/builtins.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/builtins.c.o: ../src/builtins.c
src/CMakeFiles/dc_shell.dir/builtins.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/dc_shell.dir/builtins.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/builtins.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/builtins.c.o -MF CMakeFiles/dc_shell.dir/builtins.c.o.d -o CMakeFiles/dc_shell.dir/builtins.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/builtins.c

src/CMakeFiles/dc_shell.dir/builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/builtins.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/builtins.c > CMakeFiles/dc_shell.dir/builtins.c.i

src/CMakeFiles/dc_shell.dir/builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/builtins.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/builtins.c -o CMakeFiles/dc_shell.dir/builtins.c.s

src/CMakeFiles/dc_shell.dir/command.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/command.c.o: ../src/command.c
src/CMakeFiles/dc_shell.dir/command.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/dc_shell.dir/command.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/command.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/command.c.o -MF CMakeFiles/dc_shell.dir/command.c.o.d -o CMakeFiles/dc_shell.dir/command.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/command.c

src/CMakeFiles/dc_shell.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/command.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/command.c > CMakeFiles/dc_shell.dir/command.c.i

src/CMakeFiles/dc_shell.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/command.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/command.c -o CMakeFiles/dc_shell.dir/command.c.s

src/CMakeFiles/dc_shell.dir/execute.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/execute.c.o: ../src/execute.c
src/CMakeFiles/dc_shell.dir/execute.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/dc_shell.dir/execute.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/execute.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/execute.c.o -MF CMakeFiles/dc_shell.dir/execute.c.o.d -o CMakeFiles/dc_shell.dir/execute.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/execute.c

src/CMakeFiles/dc_shell.dir/execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/execute.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/execute.c > CMakeFiles/dc_shell.dir/execute.c.i

src/CMakeFiles/dc_shell.dir/execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/execute.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/execute.c -o CMakeFiles/dc_shell.dir/execute.c.s

src/CMakeFiles/dc_shell.dir/input.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/input.c.o: ../src/input.c
src/CMakeFiles/dc_shell.dir/input.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/dc_shell.dir/input.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/input.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/input.c.o -MF CMakeFiles/dc_shell.dir/input.c.o.d -o CMakeFiles/dc_shell.dir/input.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/input.c

src/CMakeFiles/dc_shell.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/input.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/input.c > CMakeFiles/dc_shell.dir/input.c.i

src/CMakeFiles/dc_shell.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/input.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/input.c -o CMakeFiles/dc_shell.dir/input.c.s

src/CMakeFiles/dc_shell.dir/shell.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/shell.c.o: ../src/shell.c
src/CMakeFiles/dc_shell.dir/shell.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/dc_shell.dir/shell.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/shell.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/shell.c.o -MF CMakeFiles/dc_shell.dir/shell.c.o.d -o CMakeFiles/dc_shell.dir/shell.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/shell.c

src/CMakeFiles/dc_shell.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/shell.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/shell.c > CMakeFiles/dc_shell.dir/shell.c.i

src/CMakeFiles/dc_shell.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/shell.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/shell.c -o CMakeFiles/dc_shell.dir/shell.c.s

src/CMakeFiles/dc_shell.dir/shell_impl.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/shell_impl.c.o: ../src/shell_impl.c
src/CMakeFiles/dc_shell.dir/shell_impl.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/dc_shell.dir/shell_impl.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/shell_impl.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/shell_impl.c.o -MF CMakeFiles/dc_shell.dir/shell_impl.c.o.d -o CMakeFiles/dc_shell.dir/shell_impl.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/shell_impl.c

src/CMakeFiles/dc_shell.dir/shell_impl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/shell_impl.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/shell_impl.c > CMakeFiles/dc_shell.dir/shell_impl.c.i

src/CMakeFiles/dc_shell.dir/shell_impl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/shell_impl.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/shell_impl.c -o CMakeFiles/dc_shell.dir/shell_impl.c.s

src/CMakeFiles/dc_shell.dir/util.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/util.c.o: ../src/util.c
src/CMakeFiles/dc_shell.dir/util.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/dc_shell.dir/util.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/util.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/util.c.o -MF CMakeFiles/dc_shell.dir/util.c.o.d -o CMakeFiles/dc_shell.dir/util.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/util.c

src/CMakeFiles/dc_shell.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/util.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/util.c > CMakeFiles/dc_shell.dir/util.c.i

src/CMakeFiles/dc_shell.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/util.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/util.c -o CMakeFiles/dc_shell.dir/util.c.s

src/CMakeFiles/dc_shell.dir/main.c.o: src/CMakeFiles/dc_shell.dir/flags.make
src/CMakeFiles/dc_shell.dir/main.c.o: ../src/main.c
src/CMakeFiles/dc_shell.dir/main.c.o: src/CMakeFiles/dc_shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/CMakeFiles/dc_shell.dir/main.c.o"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/home/raith/work/COMP-4981/Assignment-1/src/main.c -- /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/dc_shell.dir/main.c.o -MF CMakeFiles/dc_shell.dir/main.c.o.d -o CMakeFiles/dc_shell.dir/main.c.o -c /home/raith/work/COMP-4981/Assignment-1/src/main.c

src/CMakeFiles/dc_shell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dc_shell.dir/main.c.i"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raith/work/COMP-4981/Assignment-1/src/main.c > CMakeFiles/dc_shell.dir/main.c.i

src/CMakeFiles/dc_shell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dc_shell.dir/main.c.s"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raith/work/COMP-4981/Assignment-1/src/main.c -o CMakeFiles/dc_shell.dir/main.c.s

# Object files for target dc_shell
dc_shell_OBJECTS = \
"CMakeFiles/dc_shell.dir/builtins.c.o" \
"CMakeFiles/dc_shell.dir/command.c.o" \
"CMakeFiles/dc_shell.dir/execute.c.o" \
"CMakeFiles/dc_shell.dir/input.c.o" \
"CMakeFiles/dc_shell.dir/shell.c.o" \
"CMakeFiles/dc_shell.dir/shell_impl.c.o" \
"CMakeFiles/dc_shell.dir/util.c.o" \
"CMakeFiles/dc_shell.dir/main.c.o"

# External object files for target dc_shell
dc_shell_EXTERNAL_OBJECTS =

src/dc_shell: src/CMakeFiles/dc_shell.dir/builtins.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/command.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/execute.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/input.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/shell.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/shell_impl.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/util.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/main.c.o
src/dc_shell: src/CMakeFiles/dc_shell.dir/build.make
src/dc_shell: /usr/lib/x86_64-linux-gnu/libm.so
src/dc_shell: /usr/local/lib/libdc_error.so
src/dc_shell: /usr/local/lib/libdc_posix.so
src/dc_shell: /usr/local/lib/libdc_util.so
src/dc_shell: /usr/local/lib/libdc_fsm.so
src/dc_shell: /usr/local/lib/libdc_application.so
src/dc_shell: src/CMakeFiles/dc_shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable dc_shell"
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dc_shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/dc_shell.dir/build: src/dc_shell
.PHONY : src/CMakeFiles/dc_shell.dir/build

src/CMakeFiles/dc_shell.dir/clean:
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/dc_shell.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/dc_shell.dir/clean

src/CMakeFiles/dc_shell.dir/depend:
	cd /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/raith/work/COMP-4981/Assignment-1 /home/raith/work/COMP-4981/Assignment-1/src /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src /home/raith/work/COMP-4981/Assignment-1/cmake-build-debug/src/CMakeFiles/dc_shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/dc_shell.dir/depend

