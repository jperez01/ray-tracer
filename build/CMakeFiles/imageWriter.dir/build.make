# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/juanperez/documents/projects/ray-tracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/juanperez/documents/projects/ray-tracer/build

# Include any dependencies generated for this target.
include CMakeFiles/imageWriter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/imageWriter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/imageWriter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imageWriter.dir/flags.make

CMakeFiles/imageWriter.dir/src/main.cpp.o: CMakeFiles/imageWriter.dir/flags.make
CMakeFiles/imageWriter.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/imageWriter.dir/src/main.cpp.o: CMakeFiles/imageWriter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/juanperez/documents/projects/ray-tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imageWriter.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/imageWriter.dir/src/main.cpp.o -MF CMakeFiles/imageWriter.dir/src/main.cpp.o.d -o CMakeFiles/imageWriter.dir/src/main.cpp.o -c /Users/juanperez/documents/projects/ray-tracer/src/main.cpp

CMakeFiles/imageWriter.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imageWriter.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/juanperez/documents/projects/ray-tracer/src/main.cpp > CMakeFiles/imageWriter.dir/src/main.cpp.i

CMakeFiles/imageWriter.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imageWriter.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/juanperez/documents/projects/ray-tracer/src/main.cpp -o CMakeFiles/imageWriter.dir/src/main.cpp.s

# Object files for target imageWriter
imageWriter_OBJECTS = \
"CMakeFiles/imageWriter.dir/src/main.cpp.o"

# External object files for target imageWriter
imageWriter_EXTERNAL_OBJECTS =

imageWriter: CMakeFiles/imageWriter.dir/src/main.cpp.o
imageWriter: CMakeFiles/imageWriter.dir/build.make
imageWriter: /usr/local/lib/libgtest.a
imageWriter: /usr/local/lib/libgtest_main.a
imageWriter: libprimitives.a
imageWriter: libdisplay.a
imageWriter: libshapes.a
imageWriter: libimages.a
imageWriter: liblights.a
imageWriter: /usr/local/lib/libgtest.a
imageWriter: CMakeFiles/imageWriter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/juanperez/documents/projects/ray-tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable imageWriter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imageWriter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imageWriter.dir/build: imageWriter
.PHONY : CMakeFiles/imageWriter.dir/build

CMakeFiles/imageWriter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imageWriter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imageWriter.dir/clean

CMakeFiles/imageWriter.dir/depend:
	cd /Users/juanperez/documents/projects/ray-tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/juanperez/documents/projects/ray-tracer /Users/juanperez/documents/projects/ray-tracer /Users/juanperez/documents/projects/ray-tracer/build /Users/juanperez/documents/projects/ray-tracer/build /Users/juanperez/documents/projects/ray-tracer/build/CMakeFiles/imageWriter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imageWriter.dir/depend

