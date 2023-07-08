# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build

# Include any dependencies generated for this target.
include src/CMakeFiles/WordFrequencyExe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/WordFrequencyExe.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/WordFrequencyExe.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/WordFrequencyExe.dir/flags.make

src/CMakeFiles/WordFrequencyExe.dir/main.c.o: src/CMakeFiles/WordFrequencyExe.dir/flags.make
src/CMakeFiles/WordFrequencyExe.dir/main.c.o: /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/main.c
src/CMakeFiles/WordFrequencyExe.dir/main.c.o: src/CMakeFiles/WordFrequencyExe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/WordFrequencyExe.dir/main.c.o"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/WordFrequencyExe.dir/main.c.o -MF CMakeFiles/WordFrequencyExe.dir/main.c.o.d -o CMakeFiles/WordFrequencyExe.dir/main.c.o -c /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/main.c

src/CMakeFiles/WordFrequencyExe.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordFrequencyExe.dir/main.c.i"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/main.c > CMakeFiles/WordFrequencyExe.dir/main.c.i

src/CMakeFiles/WordFrequencyExe.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordFrequencyExe.dir/main.c.s"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/main.c -o CMakeFiles/WordFrequencyExe.dir/main.c.s

# Object files for target WordFrequencyExe
WordFrequencyExe_OBJECTS = \
"CMakeFiles/WordFrequencyExe.dir/main.c.o"

# External object files for target WordFrequencyExe
WordFrequencyExe_EXTERNAL_OBJECTS =

src/WordFrequencyExe: src/CMakeFiles/WordFrequencyExe.dir/main.c.o
src/WordFrequencyExe: src/CMakeFiles/WordFrequencyExe.dir/build.make
src/WordFrequencyExe: src/libWordFrequency.a
src/WordFrequencyExe: src/CMakeFiles/WordFrequencyExe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable WordFrequencyExe"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WordFrequencyExe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/WordFrequencyExe.dir/build: src/WordFrequencyExe
.PHONY : src/CMakeFiles/WordFrequencyExe.dir/build

src/CMakeFiles/WordFrequencyExe.dir/clean:
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && $(CMAKE_COMMAND) -P CMakeFiles/WordFrequencyExe.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/WordFrequencyExe.dir/clean

src/CMakeFiles/WordFrequencyExe.dir/depend:
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src/CMakeFiles/WordFrequencyExe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/WordFrequencyExe.dir/depend
