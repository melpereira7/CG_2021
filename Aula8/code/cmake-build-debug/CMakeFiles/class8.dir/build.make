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
CMAKE_SOURCE_DIR = C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/class8.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class8.dir/flags.make

CMakeFiles/class8.dir/catmull-rom.cpp.obj: CMakeFiles/class8.dir/flags.make
CMakeFiles/class8.dir/catmull-rom.cpp.obj: CMakeFiles/class8.dir/includes_CXX.rsp
CMakeFiles/class8.dir/catmull-rom.cpp.obj: ../catmull-rom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class8.dir/catmull-rom.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\class8.dir\catmull-rom.cpp.obj -c C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\catmull-rom.cpp

CMakeFiles/class8.dir/catmull-rom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class8.dir/catmull-rom.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\catmull-rom.cpp > CMakeFiles\class8.dir\catmull-rom.cpp.i

CMakeFiles/class8.dir/catmull-rom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class8.dir/catmull-rom.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\catmull-rom.cpp -o CMakeFiles\class8.dir\catmull-rom.cpp.s

# Object files for target class8
class8_OBJECTS = \
"CMakeFiles/class8.dir/catmull-rom.cpp.obj"

# External object files for target class8
class8_EXTERNAL_OBJECTS =

class8.exe: CMakeFiles/class8.dir/catmull-rom.cpp.obj
class8.exe: CMakeFiles/class8.dir/build.make
class8.exe: /glut/glut32.lib
class8.exe: /glut/glut32.lib
class8.exe: CMakeFiles/class8.dir/linklibs.rsp
class8.exe: CMakeFiles/class8.dir/objects1.rsp
class8.exe: CMakeFiles/class8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class8.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\class8.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class8.dir/build: class8.exe

.PHONY : CMakeFiles/class8.dir/build

CMakeFiles/class8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\class8.dir\cmake_clean.cmake
.PHONY : CMakeFiles/class8.dir/clean

CMakeFiles/class8.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\cmake-build-debug C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\cmake-build-debug C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula8\code\cmake-build-debug\CMakeFiles\class8.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class8.dir/depend

