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
CMAKE_SOURCE_DIR = C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/class6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class6.dir/flags.make

CMakeFiles/class6.dir/main.cpp.obj: CMakeFiles/class6.dir/flags.make
CMakeFiles/class6.dir/main.cpp.obj: CMakeFiles/class6.dir/includes_CXX.rsp
CMakeFiles/class6.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class6.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\class6.dir\main.cpp.obj -c C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\main.cpp

CMakeFiles/class6.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class6.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\main.cpp > CMakeFiles\class6.dir\main.cpp.i

CMakeFiles/class6.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class6.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\main.cpp -o CMakeFiles\class6.dir\main.cpp.s

# Object files for target class6
class6_OBJECTS = \
"CMakeFiles/class6.dir/main.cpp.obj"

# External object files for target class6
class6_EXTERNAL_OBJECTS =

class6.exe: CMakeFiles/class6.dir/main.cpp.obj
class6.exe: CMakeFiles/class6.dir/build.make
class6.exe: C:/Users/melan/Desktop/Aulas/CG/.toolkits/glut/glut32.lib
class6.exe: C:/Users/melan/Desktop/Aulas/CG/.toolkits/devil/DevIL.lib
class6.exe: C:/Users/melan/Desktop/Aulas/CG/.toolkits/glew/glew32.lib
class6.exe: CMakeFiles/class6.dir/linklibs.rsp
class6.exe: CMakeFiles/class6.dir/objects1.rsp
class6.exe: CMakeFiles/class6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class6.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\class6.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class6.dir/build: class6.exe

.PHONY : CMakeFiles/class6.dir/build

CMakeFiles/class6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\class6.dir\cmake_clean.cmake
.PHONY : CMakeFiles/class6.dir/clean

CMakeFiles/class6.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\cmake-build-release C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\cmake-build-release C:\Users\melan\Desktop\Aulas\CG\Praticas\Aula7\code\cmake-build-release\CMakeFiles\class6.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class6.dir/depend

