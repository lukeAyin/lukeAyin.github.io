# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\Training\CMini\word_frequency\WordFrequency

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\Training\CMini\word_frequency\WordFrequency\tests

# Include any dependencies generated for this target.
include tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/depend.make

# Include the progress variables for this target.
include tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/flags.make

tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj: tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/flags.make
tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj: tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/includes_CXX.rsp
tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj: googletest/googletest/src/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Training\CMini\word_frequency\WordFrequency\tests\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj"
	cd /d F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gtest_main.dir\src\gtest_main.cc.obj -c F:\Training\CMini\word_frequency\WordFrequency\tests\googletest\googletest\src\gtest_main.cc

tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd /d F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Training\CMini\word_frequency\WordFrequency\tests\googletest\googletest\src\gtest_main.cc > CMakeFiles\gtest_main.dir\src\gtest_main.cc.i

tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd /d F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Training\CMini\word_frequency\WordFrequency\tests\googletest\googletest\src\gtest_main.cc -o CMakeFiles\gtest_main.dir\src\gtest_main.cc.s

# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

tests/googletest/googlemock/gtest/libgtest_main.a: tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj
tests/googletest/googlemock/gtest/libgtest_main.a: tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build.make
tests/googletest/googlemock/gtest/libgtest_main.a: tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\Training\CMini\word_frequency\WordFrequency\tests\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest_main.a"
	cd /d F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest && $(CMAKE_COMMAND) -P CMakeFiles\gtest_main.dir\cmake_clean_target.cmake
	cd /d F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gtest_main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build: tests/googletest/googlemock/gtest/libgtest_main.a

.PHONY : tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/build

tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/clean:
	cd /d F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest && $(CMAKE_COMMAND) -P CMakeFiles\gtest_main.dir\cmake_clean.cmake
.PHONY : tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/clean

tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\Training\CMini\word_frequency\WordFrequency F:\Training\CMini\word_frequency\WordFrequency\tests\googletest\googletest F:\Training\CMini\word_frequency\WordFrequency\tests F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest F:\Training\CMini\word_frequency\WordFrequency\tests\tests\googletest\googlemock\gtest\CMakeFiles\gtest_main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/googletest/googlemock/gtest/CMakeFiles/gtest_main.dir/depend

