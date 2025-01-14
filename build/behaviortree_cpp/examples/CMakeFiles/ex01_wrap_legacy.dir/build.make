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
CMAKE_SOURCE_DIR = /home/frida/idk_anymore/src/BehaviorTree.CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frida/idk_anymore/build/behaviortree_cpp

# Include any dependencies generated for this target.
include examples/CMakeFiles/ex01_wrap_legacy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/ex01_wrap_legacy.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/ex01_wrap_legacy.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/ex01_wrap_legacy.dir/flags.make

examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o: examples/CMakeFiles/ex01_wrap_legacy.dir/flags.make
examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o: /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/ex01_wrap_legacy.cpp
examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o: examples/CMakeFiles/ex01_wrap_legacy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/frida/idk_anymore/build/behaviortree_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o -MF CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o.d -o CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o -c /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/ex01_wrap_legacy.cpp

examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.i"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/ex01_wrap_legacy.cpp > CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.i

examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.s"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/ex01_wrap_legacy.cpp -o CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.s

# Object files for target ex01_wrap_legacy
ex01_wrap_legacy_OBJECTS = \
"CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o"

# External object files for target ex01_wrap_legacy
ex01_wrap_legacy_EXTERNAL_OBJECTS =

examples/ex01_wrap_legacy: examples/CMakeFiles/ex01_wrap_legacy.dir/ex01_wrap_legacy.cpp.o
examples/ex01_wrap_legacy: examples/CMakeFiles/ex01_wrap_legacy.dir/build.make
examples/ex01_wrap_legacy: sample_nodes/lib/libbt_sample_nodes.a
examples/ex01_wrap_legacy: libbehaviortree_cpp.so
examples/ex01_wrap_legacy: /opt/ros/humble/lib/libament_index_cpp.so
examples/ex01_wrap_legacy: /usr/lib/x86_64-linux-gnu/libzmq.so
examples/ex01_wrap_legacy: /usr/lib/x86_64-linux-gnu/libsqlite3.so
examples/ex01_wrap_legacy: examples/CMakeFiles/ex01_wrap_legacy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/frida/idk_anymore/build/behaviortree_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex01_wrap_legacy"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex01_wrap_legacy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/ex01_wrap_legacy.dir/build: examples/ex01_wrap_legacy
.PHONY : examples/CMakeFiles/ex01_wrap_legacy.dir/build

examples/CMakeFiles/ex01_wrap_legacy.dir/clean:
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/ex01_wrap_legacy.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/ex01_wrap_legacy.dir/clean

examples/CMakeFiles/ex01_wrap_legacy.dir/depend:
	cd /home/frida/idk_anymore/build/behaviortree_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frida/idk_anymore/src/BehaviorTree.CPP /home/frida/idk_anymore/src/BehaviorTree.CPP/examples /home/frida/idk_anymore/build/behaviortree_cpp /home/frida/idk_anymore/build/behaviortree_cpp/examples /home/frida/idk_anymore/build/behaviortree_cpp/examples/CMakeFiles/ex01_wrap_legacy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/ex01_wrap_legacy.dir/depend

