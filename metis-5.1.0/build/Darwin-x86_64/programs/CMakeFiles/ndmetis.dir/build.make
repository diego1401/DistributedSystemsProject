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
include programs/CMakeFiles/ndmetis.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include programs/CMakeFiles/ndmetis.dir/compiler_depend.make

# Include the progress variables for this target.
include programs/CMakeFiles/ndmetis.dir/progress.make

# Include the compile flags for this target's objects.
include programs/CMakeFiles/ndmetis.dir/flags.make

programs/CMakeFiles/ndmetis.dir/ndmetis.c.o: programs/CMakeFiles/ndmetis.dir/flags.make
programs/CMakeFiles/ndmetis.dir/ndmetis.c.o: ../../programs/ndmetis.c
programs/CMakeFiles/ndmetis.dir/ndmetis.c.o: programs/CMakeFiles/ndmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object programs/CMakeFiles/ndmetis.dir/ndmetis.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/ndmetis.dir/ndmetis.c.o -MF CMakeFiles/ndmetis.dir/ndmetis.c.o.d -o CMakeFiles/ndmetis.dir/ndmetis.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/ndmetis.c

programs/CMakeFiles/ndmetis.dir/ndmetis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ndmetis.dir/ndmetis.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/ndmetis.c > CMakeFiles/ndmetis.dir/ndmetis.c.i

programs/CMakeFiles/ndmetis.dir/ndmetis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ndmetis.dir/ndmetis.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/ndmetis.c -o CMakeFiles/ndmetis.dir/ndmetis.c.s

programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o: programs/CMakeFiles/ndmetis.dir/flags.make
programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o: ../../programs/cmdline_ndmetis.c
programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o: programs/CMakeFiles/ndmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o -MF CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o.d -o CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/cmdline_ndmetis.c

programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/cmdline_ndmetis.c > CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.i

programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/cmdline_ndmetis.c -o CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.s

programs/CMakeFiles/ndmetis.dir/io.c.o: programs/CMakeFiles/ndmetis.dir/flags.make
programs/CMakeFiles/ndmetis.dir/io.c.o: ../../programs/io.c
programs/CMakeFiles/ndmetis.dir/io.c.o: programs/CMakeFiles/ndmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object programs/CMakeFiles/ndmetis.dir/io.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/ndmetis.dir/io.c.o -MF CMakeFiles/ndmetis.dir/io.c.o.d -o CMakeFiles/ndmetis.dir/io.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/io.c

programs/CMakeFiles/ndmetis.dir/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ndmetis.dir/io.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/io.c > CMakeFiles/ndmetis.dir/io.c.i

programs/CMakeFiles/ndmetis.dir/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ndmetis.dir/io.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/io.c -o CMakeFiles/ndmetis.dir/io.c.s

programs/CMakeFiles/ndmetis.dir/smbfactor.c.o: programs/CMakeFiles/ndmetis.dir/flags.make
programs/CMakeFiles/ndmetis.dir/smbfactor.c.o: ../../programs/smbfactor.c
programs/CMakeFiles/ndmetis.dir/smbfactor.c.o: programs/CMakeFiles/ndmetis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object programs/CMakeFiles/ndmetis.dir/smbfactor.c.o"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT programs/CMakeFiles/ndmetis.dir/smbfactor.c.o -MF CMakeFiles/ndmetis.dir/smbfactor.c.o.d -o CMakeFiles/ndmetis.dir/smbfactor.c.o -c /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/smbfactor.c

programs/CMakeFiles/ndmetis.dir/smbfactor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ndmetis.dir/smbfactor.c.i"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/smbfactor.c > CMakeFiles/ndmetis.dir/smbfactor.c.i

programs/CMakeFiles/ndmetis.dir/smbfactor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ndmetis.dir/smbfactor.c.s"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs/smbfactor.c -o CMakeFiles/ndmetis.dir/smbfactor.c.s

# Object files for target ndmetis
ndmetis_OBJECTS = \
"CMakeFiles/ndmetis.dir/ndmetis.c.o" \
"CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o" \
"CMakeFiles/ndmetis.dir/io.c.o" \
"CMakeFiles/ndmetis.dir/smbfactor.c.o"

# External object files for target ndmetis
ndmetis_EXTERNAL_OBJECTS =

programs/ndmetis: programs/CMakeFiles/ndmetis.dir/ndmetis.c.o
programs/ndmetis: programs/CMakeFiles/ndmetis.dir/cmdline_ndmetis.c.o
programs/ndmetis: programs/CMakeFiles/ndmetis.dir/io.c.o
programs/ndmetis: programs/CMakeFiles/ndmetis.dir/smbfactor.c.o
programs/ndmetis: programs/CMakeFiles/ndmetis.dir/build.make
programs/ndmetis: libmetis/libmetis.dylib
programs/ndmetis: programs/CMakeFiles/ndmetis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ndmetis"
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndmetis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
programs/CMakeFiles/ndmetis.dir/build: programs/ndmetis
.PHONY : programs/CMakeFiles/ndmetis.dir/build

programs/CMakeFiles/ndmetis.dir/clean:
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs && $(CMAKE_COMMAND) -P CMakeFiles/ndmetis.dir/cmake_clean.cmake
.PHONY : programs/CMakeFiles/ndmetis.dir/clean

programs/CMakeFiles/ndmetis.dir/depend:
	cd /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0 /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/programs /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64 /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs /Users/Diego/Documents/SEM6/CSE305/CSE305_project/metis-5.1.0/build/Darwin-x86_64/programs/CMakeFiles/ndmetis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : programs/CMakeFiles/ndmetis.dir/depend

