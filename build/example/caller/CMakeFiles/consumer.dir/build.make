# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kai/mrpc/mrpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kai/mrpc/mrpc/build

# Include any dependencies generated for this target.
include example/caller/CMakeFiles/consumer.dir/depend.make

# Include the progress variables for this target.
include example/caller/CMakeFiles/consumer.dir/progress.make

# Include the compile flags for this target's objects.
include example/caller/CMakeFiles/consumer.dir/flags.make

example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o: example/caller/CMakeFiles/consumer.dir/flags.make
example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o: ../example/caller/callfriendservice.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kai/mrpc/mrpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o"
	cd /home/kai/mrpc/mrpc/build/example/caller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/consumer.dir/callfriendservice.cc.o -c /home/kai/mrpc/mrpc/example/caller/callfriendservice.cc

example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/consumer.dir/callfriendservice.cc.i"
	cd /home/kai/mrpc/mrpc/build/example/caller && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kai/mrpc/mrpc/example/caller/callfriendservice.cc > CMakeFiles/consumer.dir/callfriendservice.cc.i

example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/consumer.dir/callfriendservice.cc.s"
	cd /home/kai/mrpc/mrpc/build/example/caller && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kai/mrpc/mrpc/example/caller/callfriendservice.cc -o CMakeFiles/consumer.dir/callfriendservice.cc.s

example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.requires:

.PHONY : example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.requires

example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.provides: example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.requires
	$(MAKE) -f example/caller/CMakeFiles/consumer.dir/build.make example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.provides.build
.PHONY : example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.provides

example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.provides.build: example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o


example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o: example/caller/CMakeFiles/consumer.dir/flags.make
example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o: ../example/friend.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kai/mrpc/mrpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o"
	cd /home/kai/mrpc/mrpc/build/example/caller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/consumer.dir/__/friend.pb.cc.o -c /home/kai/mrpc/mrpc/example/friend.pb.cc

example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/consumer.dir/__/friend.pb.cc.i"
	cd /home/kai/mrpc/mrpc/build/example/caller && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kai/mrpc/mrpc/example/friend.pb.cc > CMakeFiles/consumer.dir/__/friend.pb.cc.i

example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/consumer.dir/__/friend.pb.cc.s"
	cd /home/kai/mrpc/mrpc/build/example/caller && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kai/mrpc/mrpc/example/friend.pb.cc -o CMakeFiles/consumer.dir/__/friend.pb.cc.s

example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.requires:

.PHONY : example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.requires

example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.provides: example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.requires
	$(MAKE) -f example/caller/CMakeFiles/consumer.dir/build.make example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.provides.build
.PHONY : example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.provides

example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.provides.build: example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o


# Object files for target consumer
consumer_OBJECTS = \
"CMakeFiles/consumer.dir/callfriendservice.cc.o" \
"CMakeFiles/consumer.dir/__/friend.pb.cc.o"

# External object files for target consumer
consumer_EXTERNAL_OBJECTS =

../bin/consumer: example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o
../bin/consumer: example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o
../bin/consumer: example/caller/CMakeFiles/consumer.dir/build.make
../bin/consumer: ../lib/libmrpc.a
../bin/consumer: example/caller/CMakeFiles/consumer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kai/mrpc/mrpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../../bin/consumer"
	cd /home/kai/mrpc/mrpc/build/example/caller && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/consumer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/caller/CMakeFiles/consumer.dir/build: ../bin/consumer

.PHONY : example/caller/CMakeFiles/consumer.dir/build

example/caller/CMakeFiles/consumer.dir/requires: example/caller/CMakeFiles/consumer.dir/callfriendservice.cc.o.requires
example/caller/CMakeFiles/consumer.dir/requires: example/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o.requires

.PHONY : example/caller/CMakeFiles/consumer.dir/requires

example/caller/CMakeFiles/consumer.dir/clean:
	cd /home/kai/mrpc/mrpc/build/example/caller && $(CMAKE_COMMAND) -P CMakeFiles/consumer.dir/cmake_clean.cmake
.PHONY : example/caller/CMakeFiles/consumer.dir/clean

example/caller/CMakeFiles/consumer.dir/depend:
	cd /home/kai/mrpc/mrpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kai/mrpc/mrpc /home/kai/mrpc/mrpc/example/caller /home/kai/mrpc/mrpc/build /home/kai/mrpc/mrpc/build/example/caller /home/kai/mrpc/mrpc/build/example/caller/CMakeFiles/consumer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/caller/CMakeFiles/consumer.dir/depend

