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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/beckb/Dev/repos/2dphysics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/beckb/Dev/repos/2dphysics/build

# Include any dependencies generated for this target.
include CMakeFiles/2dphysics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/2dphysics.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/2dphysics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2dphysics.dir/flags.make

CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o: ../src/mathfuncs.cpp
CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o -MF CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o.d -o CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/mathfuncs.cpp

CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/mathfuncs.cpp > CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.i

CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/mathfuncs.cpp -o CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.s

CMakeFiles/2dphysics.dir/src/main.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/2dphysics.dir/src/main.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/2dphysics.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/main.cpp.o -MF CMakeFiles/2dphysics.dir/src/main.cpp.o.d -o CMakeFiles/2dphysics.dir/src/main.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/main.cpp

CMakeFiles/2dphysics.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/main.cpp > CMakeFiles/2dphysics.dir/src/main.cpp.i

CMakeFiles/2dphysics.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/main.cpp -o CMakeFiles/2dphysics.dir/src/main.cpp.s

CMakeFiles/2dphysics.dir/src/world.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/world.cpp.o: ../src/world.cpp
CMakeFiles/2dphysics.dir/src/world.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/2dphysics.dir/src/world.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/world.cpp.o -MF CMakeFiles/2dphysics.dir/src/world.cpp.o.d -o CMakeFiles/2dphysics.dir/src/world.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/world.cpp

CMakeFiles/2dphysics.dir/src/world.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/world.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/world.cpp > CMakeFiles/2dphysics.dir/src/world.cpp.i

CMakeFiles/2dphysics.dir/src/world.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/world.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/world.cpp -o CMakeFiles/2dphysics.dir/src/world.cpp.s

CMakeFiles/2dphysics.dir/src/shape.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/shape.cpp.o: ../src/shape.cpp
CMakeFiles/2dphysics.dir/src/shape.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/2dphysics.dir/src/shape.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/shape.cpp.o -MF CMakeFiles/2dphysics.dir/src/shape.cpp.o.d -o CMakeFiles/2dphysics.dir/src/shape.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/shape.cpp

CMakeFiles/2dphysics.dir/src/shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/shape.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/shape.cpp > CMakeFiles/2dphysics.dir/src/shape.cpp.i

CMakeFiles/2dphysics.dir/src/shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/shape.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/shape.cpp -o CMakeFiles/2dphysics.dir/src/shape.cpp.s

CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o: ../src/rigidbody.cpp
CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o -MF CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o.d -o CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/rigidbody.cpp

CMakeFiles/2dphysics.dir/src/rigidbody.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/rigidbody.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/rigidbody.cpp > CMakeFiles/2dphysics.dir/src/rigidbody.cpp.i

CMakeFiles/2dphysics.dir/src/rigidbody.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/rigidbody.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/rigidbody.cpp -o CMakeFiles/2dphysics.dir/src/rigidbody.cpp.s

CMakeFiles/2dphysics.dir/src/collisions.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/collisions.cpp.o: ../src/collisions.cpp
CMakeFiles/2dphysics.dir/src/collisions.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/2dphysics.dir/src/collisions.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/collisions.cpp.o -MF CMakeFiles/2dphysics.dir/src/collisions.cpp.o.d -o CMakeFiles/2dphysics.dir/src/collisions.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/collisions.cpp

CMakeFiles/2dphysics.dir/src/collisions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/collisions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/collisions.cpp > CMakeFiles/2dphysics.dir/src/collisions.cpp.i

CMakeFiles/2dphysics.dir/src/collisions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/collisions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/collisions.cpp -o CMakeFiles/2dphysics.dir/src/collisions.cpp.s

CMakeFiles/2dphysics.dir/src/circle.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/circle.cpp.o: ../src/circle.cpp
CMakeFiles/2dphysics.dir/src/circle.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/2dphysics.dir/src/circle.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/circle.cpp.o -MF CMakeFiles/2dphysics.dir/src/circle.cpp.o.d -o CMakeFiles/2dphysics.dir/src/circle.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/circle.cpp

CMakeFiles/2dphysics.dir/src/circle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/circle.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/circle.cpp > CMakeFiles/2dphysics.dir/src/circle.cpp.i

CMakeFiles/2dphysics.dir/src/circle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/circle.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/circle.cpp -o CMakeFiles/2dphysics.dir/src/circle.cpp.s

CMakeFiles/2dphysics.dir/src/polygon.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/polygon.cpp.o: ../src/polygon.cpp
CMakeFiles/2dphysics.dir/src/polygon.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/2dphysics.dir/src/polygon.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/polygon.cpp.o -MF CMakeFiles/2dphysics.dir/src/polygon.cpp.o.d -o CMakeFiles/2dphysics.dir/src/polygon.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/polygon.cpp

CMakeFiles/2dphysics.dir/src/polygon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/polygon.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/polygon.cpp > CMakeFiles/2dphysics.dir/src/polygon.cpp.i

CMakeFiles/2dphysics.dir/src/polygon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/polygon.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/polygon.cpp -o CMakeFiles/2dphysics.dir/src/polygon.cpp.s

CMakeFiles/2dphysics.dir/src/scene.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/scene.cpp.o: ../src/scene.cpp
CMakeFiles/2dphysics.dir/src/scene.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/2dphysics.dir/src/scene.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/scene.cpp.o -MF CMakeFiles/2dphysics.dir/src/scene.cpp.o.d -o CMakeFiles/2dphysics.dir/src/scene.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/scene.cpp

CMakeFiles/2dphysics.dir/src/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/scene.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/scene.cpp > CMakeFiles/2dphysics.dir/src/scene.cpp.i

CMakeFiles/2dphysics.dir/src/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/scene.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/scene.cpp -o CMakeFiles/2dphysics.dir/src/scene.cpp.s

CMakeFiles/2dphysics.dir/src/AABB.cpp.o: CMakeFiles/2dphysics.dir/flags.make
CMakeFiles/2dphysics.dir/src/AABB.cpp.o: ../src/AABB.cpp
CMakeFiles/2dphysics.dir/src/AABB.cpp.o: CMakeFiles/2dphysics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/2dphysics.dir/src/AABB.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2dphysics.dir/src/AABB.cpp.o -MF CMakeFiles/2dphysics.dir/src/AABB.cpp.o.d -o CMakeFiles/2dphysics.dir/src/AABB.cpp.o -c /home/beckb/Dev/repos/2dphysics/src/AABB.cpp

CMakeFiles/2dphysics.dir/src/AABB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dphysics.dir/src/AABB.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beckb/Dev/repos/2dphysics/src/AABB.cpp > CMakeFiles/2dphysics.dir/src/AABB.cpp.i

CMakeFiles/2dphysics.dir/src/AABB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dphysics.dir/src/AABB.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beckb/Dev/repos/2dphysics/src/AABB.cpp -o CMakeFiles/2dphysics.dir/src/AABB.cpp.s

# Object files for target 2dphysics
2dphysics_OBJECTS = \
"CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o" \
"CMakeFiles/2dphysics.dir/src/main.cpp.o" \
"CMakeFiles/2dphysics.dir/src/world.cpp.o" \
"CMakeFiles/2dphysics.dir/src/shape.cpp.o" \
"CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o" \
"CMakeFiles/2dphysics.dir/src/collisions.cpp.o" \
"CMakeFiles/2dphysics.dir/src/circle.cpp.o" \
"CMakeFiles/2dphysics.dir/src/polygon.cpp.o" \
"CMakeFiles/2dphysics.dir/src/scene.cpp.o" \
"CMakeFiles/2dphysics.dir/src/AABB.cpp.o"

# External object files for target 2dphysics
2dphysics_EXTERNAL_OBJECTS =

2dphysics: CMakeFiles/2dphysics.dir/src/mathfuncs.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/main.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/world.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/shape.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/rigidbody.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/collisions.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/circle.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/polygon.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/scene.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/src/AABB.cpp.o
2dphysics: CMakeFiles/2dphysics.dir/build.make
2dphysics: /usr/lib/x86_64-linux-gnu/libSDL2.so
2dphysics: /usr/lib/x86_64-linux-gnu/libGL.so
2dphysics: CMakeFiles/2dphysics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beckb/Dev/repos/2dphysics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable 2dphysics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2dphysics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2dphysics.dir/build: 2dphysics
.PHONY : CMakeFiles/2dphysics.dir/build

CMakeFiles/2dphysics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2dphysics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2dphysics.dir/clean

CMakeFiles/2dphysics.dir/depend:
	cd /home/beckb/Dev/repos/2dphysics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beckb/Dev/repos/2dphysics /home/beckb/Dev/repos/2dphysics /home/beckb/Dev/repos/2dphysics/build /home/beckb/Dev/repos/2dphysics/build /home/beckb/Dev/repos/2dphysics/build/CMakeFiles/2dphysics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2dphysics.dir/depend

