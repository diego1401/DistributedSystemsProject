# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64

# Include any dependencies generated for this target.
include programs/CMakeFiles/gpmetis.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include programs/CMakeFiles/gpmetis.dir/compiler_depend.make

# Include the progress variables for this target.
include programs/CMakeFiles/gpmetis.dir/progress.make

# Include the compile flags for this target's objects.
include programs/CMakeFiles/gpmetis.dir/flags.make

programs/CMakeFiles/gpmetis.dir/gpmetis.c.o: programs/CMakeFiles/gpmetis.dir/flags.make
programs/CMakeFiles/gpmetis.dir/gpmetis.c.o: ../../programs/gpmetis.c
programs/CMakeFiles/gpmetis.dir/gpmetis.c.o: programs/CMakeFiles/gpmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object programs/CMakeFiles/gpmetis.dir/gpmetis.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/gpmetis.dir/gpmetis.c.o -MF CMakeFiles/gpmetis.dir/gpmetis.c.o.d -o CMakeFiles/gpmetis.dir/gpmetis.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/gpmetis.c

programs/CMakeFiles/gpmetis.dir/gpmetis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gpmetis.dir/gpmetis.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/gpmetis.c > CMakeFiles/gpmetis.dir/gpmetis.c.i

programs/CMakeFiles/gpmetis.dir/gpmetis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gpmetis.dir/gpmetis.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/gpmetis.c -o CMakeFiles/gpmetis.dir/gpmetis.c.s

programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o: programs/CMakeFiles/gpmetis.dir/flags.make
programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o: ../../programs/cmdline_gpmetis.c
programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o: programs/CMakeFiles/gpmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o -MF CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o.d -o CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/cmdline_gpmetis.c

programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/cmdline_gpmetis.c > CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.i

programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/cmdline_gpmetis.c -o CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.s

programs/CMakeFiles/gpmetis.dir/io.c.o: programs/CMakeFiles/gpmetis.dir/flags.make
programs/CMakeFiles/gpmetis.dir/io.c.o: ../../programs/io.c
programs/CMakeFiles/gpmetis.dir/io.c.o: programs/CMakeFiles/gpmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object programs/CMakeFiles/gpmetis.dir/io.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/gpmetis.dir/io.c.o -MF CMakeFiles/gpmetis.dir/io.c.o.d -o CMakeFiles/gpmetis.dir/io.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/io.c

programs/CMakeFiles/gpmetis.dir/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gpmetis.dir/io.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/io.c > CMakeFiles/gpmetis.dir/io.c.i

programs/CMakeFiles/gpmetis.dir/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gpmetis.dir/io.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/io.c -o CMakeFiles/gpmetis.dir/io.c.s

programs/CMakeFiles/gpmetis.dir/stat.c.o: programs/CMakeFiles/gpmetis.dir/flags.make
programs/CMakeFiles/gpmetis.dir/stat.c.o: ../../programs/stat.c
programs/CMakeFiles/gpmetis.dir/stat.c.o: programs/CMakeFiles/gpmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object programs/CMakeFiles/gpmetis.dir/stat.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/gpmetis.dir/stat.c.o -MF CMakeFiles/gpmetis.dir/stat.c.o.d -o CMakeFiles/gpmetis.dir/stat.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/stat.c

programs/CMakeFiles/gpmetis.dir/stat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gpmetis.dir/stat.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/stat.c > CMakeFiles/gpmetis.dir/stat.c.i

programs/CMakeFiles/gpmetis.dir/stat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gpmetis.dir/stat.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/stat.c -o CMakeFiles/gpmetis.dir/stat.c.s

# Object files for target gpmetis
gpmetis_OBJECTS = \
"CMakeFiles/gpmetis.dir/gpmetis.c.o" \
"CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o" \
"CMakeFiles/gpmetis.dir/io.c.o" \
"CMakeFiles/gpmetis.dir/stat.c.o"

# External object files for target gpmetis
gpmetis_EXTERNAL_OBJECTS =

programs/gpmetis: programs/CMakeFiles/gpmetis.dir/gpmetis.c.o
programs/gpmetis: programs/CMakeFiles/gpmetis.dir/cmdline_gpmetis.c.o
programs/gpmetis: programs/CMakeFiles/gpmetis.dir/io.c.o
programs/gpmetis: programs/CMakeFiles/gpmetis.dir/stat.c.o
programs/gpmetis: programs/CMakeFiles/gpmetis.dir/build.make
programs/gpmetis: libmetis/libmetis.dylib
programs/gpmetis: programs/CMakeFiles/gpmetis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable gpmetis"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gpmetis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
programs/CMakeFiles/gpmetis.dir/build: programs/gpmetis
.PHONY : programs/CMakeFiles/gpmetis.dir/build

programs/CMakeFiles/gpmetis.dir/clean:
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && $(CMAKE_COMMAND) -P CMakeFiles/gpmetis.dir/cmake_clean.cmake
.PHONY : programs/CMakeFiles/gpmetis.dir/clean

programs/CMakeFiles/gpmetis.dir/depend:
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0 /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64 /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs/CMakeFiles/gpmetis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : programs/CMakeFiles/gpmetis.dir/depend

