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
include examples/CMakeFiles/t02_basic_ports.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/t02_basic_ports.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/t02_basic_ports.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/t02_basic_ports.dir/flags.make

examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o: examples/CMakeFiles/t02_basic_ports.dir/flags.make
examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o: /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/t02_basic_ports.cpp
examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o: examples/CMakeFiles/t02_basic_ports.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/frida/idk_anymore/build/behaviortree_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o -MF CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o.d -o CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o -c /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/t02_basic_ports.cpp

examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.i"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/t02_basic_ports.cpp > CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.i

examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.s"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frida/idk_anymore/src/BehaviorTree.CPP/examples/t02_basic_ports.cpp -o CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.s

# Object files for target t02_basic_ports
t02_basic_ports_OBJECTS = \
"CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o"

# External object files for target t02_basic_ports
t02_basic_ports_EXTERNAL_OBJECTS =

examples/t02_basic_ports: examples/CMakeFiles/t02_basic_ports.dir/t02_basic_ports.cpp.o
examples/t02_basic_ports: examples/CMakeFiles/t02_basic_ports.dir/build.make
examples/t02_basic_ports: sample_nodes/lib/libbt_sample_nodes.a
examples/t02_basic_ports: libbehaviortree_cpp.so
examples/t02_basic_ports: /opt/ros/humble/lib/libament_index_cpp.so
examples/t02_basic_ports: /usr/lib/x86_64-linux-gnu/libzmq.so
examples/t02_basic_ports: /usr/lib/x86_64-linux-gnu/libsqlite3.so
examples/t02_basic_ports: examples/CMakeFiles/t02_basic_ports.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/frida/idk_anymore/build/behaviortree_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable t02_basic_ports"
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/t02_basic_ports.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/t02_basic_ports.dir/build: examples/t02_basic_ports
.PHONY : examples/CMakeFiles/t02_basic_ports.dir/build

examples/CMakeFiles/t02_basic_ports.dir/clean:
	cd /home/frida/idk_anymore/build/behaviortree_cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/t02_basic_ports.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/t02_basic_ports.dir/clean

examples/CMakeFiles/t02_basic_ports.dir/depend:
	cd /home/frida/idk_anymore/build/behaviortree_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frida/idk_anymore/src/BehaviorTree.CPP /home/frida/idk_anymore/src/BehaviorTree.CPP/examples /home/frida/idk_anymore/build/behaviortree_cpp /home/frida/idk_anymore/build/behaviortree_cpp/examples /home/frida/idk_anymore/build/behaviortree_cpp/examples/CMakeFiles/t02_basic_ports.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/t02_basic_ports.dir/depend

