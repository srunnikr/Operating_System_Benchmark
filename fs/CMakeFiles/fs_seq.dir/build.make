# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sreejith/coding/repo_test/cse221_operating_systems/fs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sreejith/coding/repo_test/cse221_operating_systems/fs

# Include any dependencies generated for this target.
include CMakeFiles/fs_seq.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fs_seq.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fs_seq.dir/flags.make

CMakeFiles/fs_seq.dir/src/fs_seq.c.o: CMakeFiles/fs_seq.dir/flags.make
CMakeFiles/fs_seq.dir/src/fs_seq.c.o: src/fs_seq.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sreejith/coding/repo_test/cse221_operating_systems/fs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fs_seq.dir/src/fs_seq.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fs_seq.dir/src/fs_seq.c.o   -c /home/sreejith/coding/repo_test/cse221_operating_systems/fs/src/fs_seq.c

CMakeFiles/fs_seq.dir/src/fs_seq.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fs_seq.dir/src/fs_seq.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sreejith/coding/repo_test/cse221_operating_systems/fs/src/fs_seq.c > CMakeFiles/fs_seq.dir/src/fs_seq.c.i

CMakeFiles/fs_seq.dir/src/fs_seq.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fs_seq.dir/src/fs_seq.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sreejith/coding/repo_test/cse221_operating_systems/fs/src/fs_seq.c -o CMakeFiles/fs_seq.dir/src/fs_seq.c.s

CMakeFiles/fs_seq.dir/src/fs_seq.c.o.requires:

.PHONY : CMakeFiles/fs_seq.dir/src/fs_seq.c.o.requires

CMakeFiles/fs_seq.dir/src/fs_seq.c.o.provides: CMakeFiles/fs_seq.dir/src/fs_seq.c.o.requires
	$(MAKE) -f CMakeFiles/fs_seq.dir/build.make CMakeFiles/fs_seq.dir/src/fs_seq.c.o.provides.build
.PHONY : CMakeFiles/fs_seq.dir/src/fs_seq.c.o.provides

CMakeFiles/fs_seq.dir/src/fs_seq.c.o.provides.build: CMakeFiles/fs_seq.dir/src/fs_seq.c.o


CMakeFiles/fs_seq.dir/src/utils.c.o: CMakeFiles/fs_seq.dir/flags.make
CMakeFiles/fs_seq.dir/src/utils.c.o: src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sreejith/coding/repo_test/cse221_operating_systems/fs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/fs_seq.dir/src/utils.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fs_seq.dir/src/utils.c.o   -c /home/sreejith/coding/repo_test/cse221_operating_systems/fs/src/utils.c

CMakeFiles/fs_seq.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fs_seq.dir/src/utils.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sreejith/coding/repo_test/cse221_operating_systems/fs/src/utils.c > CMakeFiles/fs_seq.dir/src/utils.c.i

CMakeFiles/fs_seq.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fs_seq.dir/src/utils.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sreejith/coding/repo_test/cse221_operating_systems/fs/src/utils.c -o CMakeFiles/fs_seq.dir/src/utils.c.s

CMakeFiles/fs_seq.dir/src/utils.c.o.requires:

.PHONY : CMakeFiles/fs_seq.dir/src/utils.c.o.requires

CMakeFiles/fs_seq.dir/src/utils.c.o.provides: CMakeFiles/fs_seq.dir/src/utils.c.o.requires
	$(MAKE) -f CMakeFiles/fs_seq.dir/build.make CMakeFiles/fs_seq.dir/src/utils.c.o.provides.build
.PHONY : CMakeFiles/fs_seq.dir/src/utils.c.o.provides

CMakeFiles/fs_seq.dir/src/utils.c.o.provides.build: CMakeFiles/fs_seq.dir/src/utils.c.o


# Object files for target fs_seq
fs_seq_OBJECTS = \
"CMakeFiles/fs_seq.dir/src/fs_seq.c.o" \
"CMakeFiles/fs_seq.dir/src/utils.c.o"

# External object files for target fs_seq
fs_seq_EXTERNAL_OBJECTS =

bin/fs_seq: CMakeFiles/fs_seq.dir/src/fs_seq.c.o
bin/fs_seq: CMakeFiles/fs_seq.dir/src/utils.c.o
bin/fs_seq: CMakeFiles/fs_seq.dir/build.make
bin/fs_seq: CMakeFiles/fs_seq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sreejith/coding/repo_test/cse221_operating_systems/fs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin/fs_seq"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fs_seq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fs_seq.dir/build: bin/fs_seq

.PHONY : CMakeFiles/fs_seq.dir/build

CMakeFiles/fs_seq.dir/requires: CMakeFiles/fs_seq.dir/src/fs_seq.c.o.requires
CMakeFiles/fs_seq.dir/requires: CMakeFiles/fs_seq.dir/src/utils.c.o.requires

.PHONY : CMakeFiles/fs_seq.dir/requires

CMakeFiles/fs_seq.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fs_seq.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fs_seq.dir/clean

CMakeFiles/fs_seq.dir/depend:
	cd /home/sreejith/coding/repo_test/cse221_operating_systems/fs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sreejith/coding/repo_test/cse221_operating_systems/fs /home/sreejith/coding/repo_test/cse221_operating_systems/fs /home/sreejith/coding/repo_test/cse221_operating_systems/fs /home/sreejith/coding/repo_test/cse221_operating_systems/fs /home/sreejith/coding/repo_test/cse221_operating_systems/fs/CMakeFiles/fs_seq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fs_seq.dir/depend

