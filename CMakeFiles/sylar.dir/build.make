# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /home/linuxbrew/.linuxbrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /home/linuxbrew/.linuxbrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspace/mysylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspace/mysylar

# Include any dependencies generated for this target.
include CMakeFiles/sylar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sylar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sylar.dir/flags.make

CMakeFiles/sylar.dir/sylar/config.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/config.o: sylar/config.cpp
CMakeFiles/sylar.dir/sylar/config.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/workspace/mysylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sylar.dir/sylar/config.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/config.o -MF CMakeFiles/sylar.dir/sylar/config.o.d -o CMakeFiles/sylar.dir/sylar/config.o -c /workspace/mysylar/sylar/config.cpp

CMakeFiles/sylar.dir/sylar/config.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/config.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/mysylar/sylar/config.cpp > CMakeFiles/sylar.dir/sylar/config.i

CMakeFiles/sylar.dir/sylar/config.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/config.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/mysylar/sylar/config.cpp -o CMakeFiles/sylar.dir/sylar/config.s

CMakeFiles/sylar.dir/sylar/fiber.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/fiber.o: sylar/fiber.cpp
CMakeFiles/sylar.dir/sylar/fiber.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/workspace/mysylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sylar.dir/sylar/fiber.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/fiber.o -MF CMakeFiles/sylar.dir/sylar/fiber.o.d -o CMakeFiles/sylar.dir/sylar/fiber.o -c /workspace/mysylar/sylar/fiber.cpp

CMakeFiles/sylar.dir/sylar/fiber.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/fiber.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/mysylar/sylar/fiber.cpp > CMakeFiles/sylar.dir/sylar/fiber.i

CMakeFiles/sylar.dir/sylar/fiber.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/fiber.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/mysylar/sylar/fiber.cpp -o CMakeFiles/sylar.dir/sylar/fiber.s

CMakeFiles/sylar.dir/sylar/log.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/log.o: sylar/log.cpp
CMakeFiles/sylar.dir/sylar/log.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/workspace/mysylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sylar.dir/sylar/log.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/log.o -MF CMakeFiles/sylar.dir/sylar/log.o.d -o CMakeFiles/sylar.dir/sylar/log.o -c /workspace/mysylar/sylar/log.cpp

CMakeFiles/sylar.dir/sylar/log.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/log.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/mysylar/sylar/log.cpp > CMakeFiles/sylar.dir/sylar/log.i

CMakeFiles/sylar.dir/sylar/log.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/log.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/mysylar/sylar/log.cpp -o CMakeFiles/sylar.dir/sylar/log.s

CMakeFiles/sylar.dir/sylar/thread.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/thread.o: sylar/thread.cpp
CMakeFiles/sylar.dir/sylar/thread.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/workspace/mysylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sylar.dir/sylar/thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/thread.o -MF CMakeFiles/sylar.dir/sylar/thread.o.d -o CMakeFiles/sylar.dir/sylar/thread.o -c /workspace/mysylar/sylar/thread.cpp

CMakeFiles/sylar.dir/sylar/thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/mysylar/sylar/thread.cpp > CMakeFiles/sylar.dir/sylar/thread.i

CMakeFiles/sylar.dir/sylar/thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/mysylar/sylar/thread.cpp -o CMakeFiles/sylar.dir/sylar/thread.s

CMakeFiles/sylar.dir/sylar/util.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/util.o: sylar/util.cpp
CMakeFiles/sylar.dir/sylar/util.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/workspace/mysylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sylar.dir/sylar/util.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/util.o -MF CMakeFiles/sylar.dir/sylar/util.o.d -o CMakeFiles/sylar.dir/sylar/util.o -c /workspace/mysylar/sylar/util.cpp

CMakeFiles/sylar.dir/sylar/util.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/util.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspace/mysylar/sylar/util.cpp > CMakeFiles/sylar.dir/sylar/util.i

CMakeFiles/sylar.dir/sylar/util.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/util.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspace/mysylar/sylar/util.cpp -o CMakeFiles/sylar.dir/sylar/util.s

# Object files for target sylar
sylar_OBJECTS = \
"CMakeFiles/sylar.dir/sylar/config.o" \
"CMakeFiles/sylar.dir/sylar/fiber.o" \
"CMakeFiles/sylar.dir/sylar/log.o" \
"CMakeFiles/sylar.dir/sylar/thread.o" \
"CMakeFiles/sylar.dir/sylar/util.o"

# External object files for target sylar
sylar_EXTERNAL_OBJECTS =

lib/libsylar.so: CMakeFiles/sylar.dir/sylar/config.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/fiber.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/log.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/thread.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/util.o
lib/libsylar.so: CMakeFiles/sylar.dir/build.make
lib/libsylar.so: CMakeFiles/sylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/workspace/mysylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library lib/libsylar.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sylar.dir/build: lib/libsylar.so
.PHONY : CMakeFiles/sylar.dir/build

CMakeFiles/sylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sylar.dir/clean

CMakeFiles/sylar.dir/depend:
	cd /workspace/mysylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/mysylar /workspace/mysylar /workspace/mysylar /workspace/mysylar /workspace/mysylar/CMakeFiles/sylar.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/sylar.dir/depend

