# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Project_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project_2.dir/flags.make

CMakeFiles/Project_2.dir/main.c.obj: CMakeFiles/Project_2.dir/flags.make
CMakeFiles/Project_2.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Project_2.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Project_2.dir\main.c.obj -c "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\main.c"

CMakeFiles/Project_2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project_2.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\main.c" > CMakeFiles\Project_2.dir\main.c.i

CMakeFiles/Project_2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project_2.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\main.c" -o CMakeFiles\Project_2.dir\main.c.s

# Object files for target Project_2
Project_2_OBJECTS = \
"CMakeFiles/Project_2.dir/main.c.obj"

# External object files for target Project_2
Project_2_EXTERNAL_OBJECTS =

Project_2.exe: CMakeFiles/Project_2.dir/main.c.obj
Project_2.exe: CMakeFiles/Project_2.dir/build.make
Project_2.exe: CMakeFiles/Project_2.dir/linklibs.rsp
Project_2.exe: CMakeFiles/Project_2.dir/objects1.rsp
Project_2.exe: CMakeFiles/Project_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Project_2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Project_2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project_2.dir/build: Project_2.exe

.PHONY : CMakeFiles/Project_2.dir/build

CMakeFiles/Project_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Project_2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Project_2.dir/clean

CMakeFiles/Project_2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2" "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2" "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\cmake-build-debug" "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\cmake-build-debug" "C:\Users\Sary\Desktop\3 First Semeseter\Data Structures\Project 2\cmake-build-debug\CMakeFiles\Project_2.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Project_2.dir/depend

