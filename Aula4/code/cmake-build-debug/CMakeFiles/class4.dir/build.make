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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/class4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class4.dir/flags.make

CMakeFiles/class4.dir/main.cpp.obj: CMakeFiles/class4.dir/flags.make
CMakeFiles/class4.dir/main.cpp.obj: CMakeFiles/class4.dir/includes_CXX.rsp
CMakeFiles/class4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class4.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\class4.dir\main.cpp.obj -c C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\main.cpp

CMakeFiles/class4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class4.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\main.cpp > CMakeFiles\class4.dir\main.cpp.i

CMakeFiles/class4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class4.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\main.cpp -o CMakeFiles\class4.dir\main.cpp.s

# Object files for target class4
class4_OBJECTS = \
"CMakeFiles/class4.dir/main.cpp.obj"

# External object files for target class4
class4_EXTERNAL_OBJECTS =

class4.exe: CMakeFiles/class4.dir/main.cpp.obj
class4.exe: CMakeFiles/class4.dir/build.make
class4.exe: /glut/glut32.lib
class4.exe: /glew/glew32.lib
class4.exe: CMakeFiles/class4.dir/linklibs.rsp
class4.exe: CMakeFiles/class4.dir/objects1.rsp
class4.exe: CMakeFiles/class4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\class4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class4.dir/build: class4.exe

.PHONY : CMakeFiles/class4.dir/build

CMakeFiles/class4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\class4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/class4.dir/clean

CMakeFiles/class4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\cmake-build-debug C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\cmake-build-debug C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula4\code\cmake-build-debug\CMakeFiles\class4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class4.dir/depend
