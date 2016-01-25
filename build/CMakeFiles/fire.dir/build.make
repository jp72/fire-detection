# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/ivan/projects/fire-detection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/projects/fire-detection/build

# Include any dependencies generated for this target.
include CMakeFiles/fire.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fire.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fire.dir/flags.make

CMakeFiles/fire.dir/detectors.cpp.o: CMakeFiles/fire.dir/flags.make
CMakeFiles/fire.dir/detectors.cpp.o: ../detectors.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/projects/fire-detection/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/fire.dir/detectors.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/fire.dir/detectors.cpp.o -c /home/ivan/projects/fire-detection/detectors.cpp

CMakeFiles/fire.dir/detectors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fire.dir/detectors.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/projects/fire-detection/detectors.cpp > CMakeFiles/fire.dir/detectors.cpp.i

CMakeFiles/fire.dir/detectors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fire.dir/detectors.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/projects/fire-detection/detectors.cpp -o CMakeFiles/fire.dir/detectors.cpp.s

CMakeFiles/fire.dir/detectors.cpp.o.requires:
.PHONY : CMakeFiles/fire.dir/detectors.cpp.o.requires

CMakeFiles/fire.dir/detectors.cpp.o.provides: CMakeFiles/fire.dir/detectors.cpp.o.requires
	$(MAKE) -f CMakeFiles/fire.dir/build.make CMakeFiles/fire.dir/detectors.cpp.o.provides.build
.PHONY : CMakeFiles/fire.dir/detectors.cpp.o.provides

CMakeFiles/fire.dir/detectors.cpp.o.provides.build: CMakeFiles/fire.dir/detectors.cpp.o

CMakeFiles/fire.dir/main.cpp.o: CMakeFiles/fire.dir/flags.make
CMakeFiles/fire.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivan/projects/fire-detection/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/fire.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/fire.dir/main.cpp.o -c /home/ivan/projects/fire-detection/main.cpp

CMakeFiles/fire.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fire.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivan/projects/fire-detection/main.cpp > CMakeFiles/fire.dir/main.cpp.i

CMakeFiles/fire.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fire.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivan/projects/fire-detection/main.cpp -o CMakeFiles/fire.dir/main.cpp.s

CMakeFiles/fire.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/fire.dir/main.cpp.o.requires

CMakeFiles/fire.dir/main.cpp.o.provides: CMakeFiles/fire.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/fire.dir/build.make CMakeFiles/fire.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/fire.dir/main.cpp.o.provides

CMakeFiles/fire.dir/main.cpp.o.provides.build: CMakeFiles/fire.dir/main.cpp.o

# Object files for target fire
fire_OBJECTS = \
"CMakeFiles/fire.dir/detectors.cpp.o" \
"CMakeFiles/fire.dir/main.cpp.o"

# External object files for target fire
fire_EXTERNAL_OBJECTS =

fire: CMakeFiles/fire.dir/detectors.cpp.o
fire: CMakeFiles/fire.dir/main.cpp.o
fire: CMakeFiles/fire.dir/build.make
fire: /usr/lib/i386-linux-gnu/libopencv_videostab.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_video.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_ts.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_superres.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_stitching.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_photo.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_ocl.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_objdetect.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_ml.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_legacy.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_imgproc.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_highgui.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_gpu.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_flann.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_features2d.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_core.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_contrib.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_calib3d.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_photo.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_legacy.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_video.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_objdetect.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_ml.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_calib3d.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_features2d.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_highgui.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_imgproc.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_flann.so.2.4.9
fire: /usr/lib/i386-linux-gnu/libopencv_core.so.2.4.9
fire: CMakeFiles/fire.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable fire"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fire.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fire.dir/build: fire
.PHONY : CMakeFiles/fire.dir/build

CMakeFiles/fire.dir/requires: CMakeFiles/fire.dir/detectors.cpp.o.requires
CMakeFiles/fire.dir/requires: CMakeFiles/fire.dir/main.cpp.o.requires
.PHONY : CMakeFiles/fire.dir/requires

CMakeFiles/fire.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fire.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fire.dir/clean

CMakeFiles/fire.dir/depend:
	cd /home/ivan/projects/fire-detection/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/projects/fire-detection /home/ivan/projects/fire-detection /home/ivan/projects/fire-detection/build /home/ivan/projects/fire-detection/build /home/ivan/projects/fire-detection/build/CMakeFiles/fire.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fire.dir/depend

