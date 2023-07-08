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
include src/CMakeFiles/WordFrequency.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/WordFrequency.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/WordFrequency.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/WordFrequency.dir/flags.make

src/CMakeFiles/WordFrequency.dir/word_frequency.c.o: src/CMakeFiles/WordFrequency.dir/flags.make
src/CMakeFiles/WordFrequency.dir/word_frequency.c.o: /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/word_frequency.c
src/CMakeFiles/WordFrequency.dir/word_frequency.c.o: src/CMakeFiles/WordFrequency.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/WordFrequency.dir/word_frequency.c.o"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/WordFrequency.dir/word_frequency.c.o -MF CMakeFiles/WordFrequency.dir/word_frequency.c.o.d -o CMakeFiles/WordFrequency.dir/word_frequency.c.o -c /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/word_frequency.c

src/CMakeFiles/WordFrequency.dir/word_frequency.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordFrequency.dir/word_frequency.c.i"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/word_frequency.c > CMakeFiles/WordFrequency.dir/word_frequency.c.i

src/CMakeFiles/WordFrequency.dir/word_frequency.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordFrequency.dir/word_frequency.c.s"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/word_frequency.c -o CMakeFiles/WordFrequency.dir/word_frequency.c.s

src/CMakeFiles/WordFrequency.dir/input.c.o: src/CMakeFiles/WordFrequency.dir/flags.make
src/CMakeFiles/WordFrequency.dir/input.c.o: /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/input.c
src/CMakeFiles/WordFrequency.dir/input.c.o: src/CMakeFiles/WordFrequency.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/WordFrequency.dir/input.c.o"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/WordFrequency.dir/input.c.o -MF CMakeFiles/WordFrequency.dir/input.c.o.d -o CMakeFiles/WordFrequency.dir/input.c.o -c /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/input.c

src/CMakeFiles/WordFrequency.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordFrequency.dir/input.c.i"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/input.c > CMakeFiles/WordFrequency.dir/input.c.i

src/CMakeFiles/WordFrequency.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordFrequency.dir/input.c.s"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/input.c -o CMakeFiles/WordFrequency.dir/input.c.s

src/CMakeFiles/WordFrequency.dir/list.c.o: src/CMakeFiles/WordFrequency.dir/flags.make
src/CMakeFiles/WordFrequency.dir/list.c.o: /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/list.c
src/CMakeFiles/WordFrequency.dir/list.c.o: src/CMakeFiles/WordFrequency.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/WordFrequency.dir/list.c.o"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/WordFrequency.dir/list.c.o -MF CMakeFiles/WordFrequency.dir/list.c.o.d -o CMakeFiles/WordFrequency.dir/list.c.o -c /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/list.c

src/CMakeFiles/WordFrequency.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordFrequency.dir/list.c.i"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/list.c > CMakeFiles/WordFrequency.dir/list.c.i

src/CMakeFiles/WordFrequency.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordFrequency.dir/list.c.s"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && /usr/sbin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src/list.c -o CMakeFiles/WordFrequency.dir/list.c.s

# Object files for target WordFrequency
WordFrequency_OBJECTS = \
"CMakeFiles/WordFrequency.dir/word_frequency.c.o" \
"CMakeFiles/WordFrequency.dir/input.c.o" \
"CMakeFiles/WordFrequency.dir/list.c.o"

# External object files for target WordFrequency
WordFrequency_EXTERNAL_OBJECTS =

src/libWordFrequency.a: src/CMakeFiles/WordFrequency.dir/word_frequency.c.o
src/libWordFrequency.a: src/CMakeFiles/WordFrequency.dir/input.c.o
src/libWordFrequency.a: src/CMakeFiles/WordFrequency.dir/list.c.o
src/libWordFrequency.a: src/CMakeFiles/WordFrequency.dir/build.make
src/libWordFrequency.a: src/CMakeFiles/WordFrequency.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libWordFrequency.a"
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && $(CMAKE_COMMAND) -P CMakeFiles/WordFrequency.dir/cmake_clean_target.cmake
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WordFrequency.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/WordFrequency.dir/build: src/libWordFrequency.a
.PHONY : src/CMakeFiles/WordFrequency.dir/build

src/CMakeFiles/WordFrequency.dir/clean:
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src && $(CMAKE_COMMAND) -P CMakeFiles/WordFrequency.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/WordFrequency.dir/clean

src/CMakeFiles/WordFrequency.dir/depend:
	cd /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/src /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src /mnt/d/code/lukeAyin.github.io/note/huawei/week3/WordFrequency/build/src/CMakeFiles/WordFrequency.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/WordFrequency.dir/depend
