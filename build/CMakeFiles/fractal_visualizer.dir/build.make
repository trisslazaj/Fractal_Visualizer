# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/trisslazaj/Desktop/Fractal_Visualizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/trisslazaj/Desktop/Fractal_Visualizer/build

# Include any dependencies generated for this target.
include CMakeFiles/fractal_visualizer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fractal_visualizer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fractal_visualizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fractal_visualizer.dir/flags.make

CMakeFiles/fractal_visualizer.dir/codegen:
.PHONY : CMakeFiles/fractal_visualizer.dir/codegen

CMakeFiles/fractal_visualizer.dir/src/main.cpp.o: CMakeFiles/fractal_visualizer.dir/flags.make
CMakeFiles/fractal_visualizer.dir/src/main.cpp.o: /Users/trisslazaj/Desktop/Fractal_Visualizer/src/main.cpp
CMakeFiles/fractal_visualizer.dir/src/main.cpp.o: CMakeFiles/fractal_visualizer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trisslazaj/Desktop/Fractal_Visualizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fractal_visualizer.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fractal_visualizer.dir/src/main.cpp.o -MF CMakeFiles/fractal_visualizer.dir/src/main.cpp.o.d -o CMakeFiles/fractal_visualizer.dir/src/main.cpp.o -c /Users/trisslazaj/Desktop/Fractal_Visualizer/src/main.cpp

CMakeFiles/fractal_visualizer.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fractal_visualizer.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trisslazaj/Desktop/Fractal_Visualizer/src/main.cpp > CMakeFiles/fractal_visualizer.dir/src/main.cpp.i

CMakeFiles/fractal_visualizer.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fractal_visualizer.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trisslazaj/Desktop/Fractal_Visualizer/src/main.cpp -o CMakeFiles/fractal_visualizer.dir/src/main.cpp.s

# Object files for target fractal_visualizer
fractal_visualizer_OBJECTS = \
"CMakeFiles/fractal_visualizer.dir/src/main.cpp.o"

# External object files for target fractal_visualizer
fractal_visualizer_EXTERNAL_OBJECTS =

bin/fractal_visualizer: CMakeFiles/fractal_visualizer.dir/src/main.cpp.o
bin/fractal_visualizer: CMakeFiles/fractal_visualizer.dir/build.make
bin/fractal_visualizer: /Library/Developer/CommandLineTools/SDKs/MacOSX14.4.sdk/System/Library/Frameworks/OpenGL.framework
bin/fractal_visualizer: libglad.a
bin/fractal_visualizer: /opt/homebrew/lib/libglfw.dylib
bin/fractal_visualizer: /Library/Developer/CommandLineTools/SDKs/MacOSX14.4.sdk/System/Library/Frameworks/OpenGL.framework
bin/fractal_visualizer: CMakeFiles/fractal_visualizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/trisslazaj/Desktop/Fractal_Visualizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/fractal_visualizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fractal_visualizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fractal_visualizer.dir/build: bin/fractal_visualizer
.PHONY : CMakeFiles/fractal_visualizer.dir/build

CMakeFiles/fractal_visualizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fractal_visualizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fractal_visualizer.dir/clean

CMakeFiles/fractal_visualizer.dir/depend:
	cd /Users/trisslazaj/Desktop/Fractal_Visualizer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/trisslazaj/Desktop/Fractal_Visualizer /Users/trisslazaj/Desktop/Fractal_Visualizer /Users/trisslazaj/Desktop/Fractal_Visualizer/build /Users/trisslazaj/Desktop/Fractal_Visualizer/build /Users/trisslazaj/Desktop/Fractal_Visualizer/build/CMakeFiles/fractal_visualizer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fractal_visualizer.dir/depend

