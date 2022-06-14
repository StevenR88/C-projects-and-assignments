# Shell
Implementation of dc_shell assignment.
Please refer to testing.pdf for unit testing.

##Features
**Reading commands**

Commands are read from stdin. An empty command should not report an error.

**Separating commands**

Any non-empty read is separated into commands. Only simple commands are supported. A simple command is a single program name with optional arguments and optional I/O redirection.

Some commands are invalid, such as a command that starts with ;

**Parsing commands**

Commands should be separated into:
- Program to run
- Arguments to the program
- stdin redirection
- stdout redirection
- stderr redirection

Redirection can include the ~ directory which will be expanded to the users home directory.

## Setup
```
mkdir cmake-build-debug
```

## Source Code Additions
```
builtins.c
command.c
execute.c
input.c
main.c
shell.c
shell_impl.c
util.c
```

```
cmake -DCMAKE_C_COMPILER="gcc" -DCMAKE_CXX_COMPILER="g++" -S . -B cmake-build-debug
```
or:

```
cmake -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -S . -B cmake-build-debug
```

## Build
```
cmake --build cmake-build-debug
cmake --build cmake-build-debug --clean-first
cmake --build cmake-build-debug --target docs
cmake --build cmake-build-debug --target format
```
