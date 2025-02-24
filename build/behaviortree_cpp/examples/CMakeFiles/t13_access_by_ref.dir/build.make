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
CMAKE_SOURCE_DIR = /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp

# Include any dependencies generated for this target.
include examples/CMakeFiles/t13_access_by_ref.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/t13_access_by_ref.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/t13_access_by_ref.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/t13_access_by_ref.dir/flags.make

examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o: examples/CMakeFiles/t13_access_by_ref.dir/flags.make
examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o: /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP/examples/t13_access_by_ref.cpp
examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o: examples/CMakeFiles/t13_access_by_ref.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o"
	cd /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o -MF CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o.d -o CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o -c /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP/examples/t13_access_by_ref.cpp

examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.i"
	cd /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP/examples/t13_access_by_ref.cpp > CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.i

examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.s"
	cd /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP/examples/t13_access_by_ref.cpp -o CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.s

# Object files for target t13_access_by_ref
t13_access_by_ref_OBJECTS = \
"CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o"

# External object files for target t13_access_by_ref
t13_access_by_ref_EXTERNAL_OBJECTS =

examples/t13_access_by_ref: examples/CMakeFiles/t13_access_by_ref.dir/t13_access_by_ref.cpp.o
examples/t13_access_by_ref: examples/CMakeFiles/t13_access_by_ref.dir/build.make
examples/t13_access_by_ref: sample_nodes/lib/libbt_sample_nodes.a
examples/t13_access_by_ref: libbehaviortree_cpp.so
examples/t13_access_by_ref: /usr/lib/x86_64-linux-gnu/libzmq.so
examples/t13_access_by_ref: /usr/lib/x86_64-linux-gnu/libsqlite3.so
examples/t13_access_by_ref: examples/CMakeFiles/t13_access_by_ref.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable t13_access_by_ref"
	cd /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/t13_access_by_ref.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/t13_access_by_ref.dir/build: examples/t13_access_by_ref
.PHONY : examples/CMakeFiles/t13_access_by_ref.dir/build

examples/CMakeFiles/t13_access_by_ref.dir/clean:
	cd /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/t13_access_by_ref.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/t13_access_by_ref.dir/clean

examples/CMakeFiles/t13_access_by_ref.dir/depend:
	cd /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP /home/larsandre/Documents/ascend/IARC10_Autonomy/src/BehaviorTree.CPP/examples /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples /home/larsandre/Documents/ascend/IARC10_Autonomy/build/behaviortree_cpp/examples/CMakeFiles/t13_access_by_ref.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/t13_access_by_ref.dir/depend

