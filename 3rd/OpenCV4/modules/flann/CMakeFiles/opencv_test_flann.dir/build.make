# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\lang\CMake3\bin\cmake.exe

# The command to remove a file.
RM = D:\lang\CMake3\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\git\github.com\opencv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\git\github.com\Pixmatica\Build\OpenCV4

# Include any dependencies generated for this target.
include modules/flann/CMakeFiles/opencv_test_flann.dir/depend.make

# Include the progress variables for this target.
include modules/flann/CMakeFiles/opencv_test_flann.dir/progress.make

# Include the compile flags for this target's objects.
include modules/flann/CMakeFiles/opencv_test_flann.dir/flags.make

modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.obj: modules/flann/CMakeFiles/opencv_test_flann.dir/flags.make
modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.obj: modules/flann/CMakeFiles/opencv_test_flann.dir/includes_CXX.rsp
modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.obj: D:/git/github.com/opencv/modules/flann/test/test_lshtable_badarg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\git\github.com\Pixmatica\Build\OpenCV4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.obj"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && C:\Qt\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\opencv_test_flann.dir\test\test_lshtable_badarg.cpp.obj -c D:\git\github.com\opencv\modules\flann\test\test_lshtable_badarg.cpp

modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.i"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\git\github.com\opencv\modules\flann\test\test_lshtable_badarg.cpp > CMakeFiles\opencv_test_flann.dir\test\test_lshtable_badarg.cpp.i

modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.s"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\git\github.com\opencv\modules\flann\test\test_lshtable_badarg.cpp -o CMakeFiles\opencv_test_flann.dir\test\test_lshtable_badarg.cpp.s

modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.obj: modules/flann/CMakeFiles/opencv_test_flann.dir/flags.make
modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.obj: modules/flann/CMakeFiles/opencv_test_flann.dir/includes_CXX.rsp
modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.obj: D:/git/github.com/opencv/modules/flann/test/test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\git\github.com\Pixmatica\Build\OpenCV4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.obj"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && C:\Qt\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\opencv_test_flann.dir\test\test_main.cpp.obj -c D:\git\github.com\opencv\modules\flann\test\test_main.cpp

modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.i"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\git\github.com\opencv\modules\flann\test\test_main.cpp > CMakeFiles\opencv_test_flann.dir\test\test_main.cpp.i

modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.s"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\git\github.com\opencv\modules\flann\test\test_main.cpp -o CMakeFiles\opencv_test_flann.dir\test\test_main.cpp.s

# Object files for target opencv_test_flann
opencv_test_flann_OBJECTS = \
"CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.obj" \
"CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.obj"

# External object files for target opencv_test_flann
opencv_test_flann_EXTERNAL_OBJECTS =

bin/opencv_test_flann.exe: modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_lshtable_badarg.cpp.obj
bin/opencv_test_flann.exe: modules/flann/CMakeFiles/opencv_test_flann.dir/test/test_main.cpp.obj
bin/opencv_test_flann.exe: modules/flann/CMakeFiles/opencv_test_flann.dir/build.make
bin/opencv_test_flann.exe: lib/libopencv_ts420.a
bin/opencv_test_flann.exe: lib/libopencv_flann420.dll.a
bin/opencv_test_flann.exe: lib/libopencv_highgui420.dll.a
bin/opencv_test_flann.exe: lib/libopencv_videoio420.dll.a
bin/opencv_test_flann.exe: lib/libopencv_imgcodecs420.dll.a
bin/opencv_test_flann.exe: lib/libopencv_imgproc420.dll.a
bin/opencv_test_flann.exe: lib/libopencv_core420.dll.a
bin/opencv_test_flann.exe: modules/flann/CMakeFiles/opencv_test_flann.dir/linklibs.rsp
bin/opencv_test_flann.exe: modules/flann/CMakeFiles/opencv_test_flann.dir/objects1.rsp
bin/opencv_test_flann.exe: modules/flann/CMakeFiles/opencv_test_flann.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\git\github.com\Pixmatica\Build\OpenCV4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ..\..\bin\opencv_test_flann.exe"
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\opencv_test_flann.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/flann/CMakeFiles/opencv_test_flann.dir/build: bin/opencv_test_flann.exe

.PHONY : modules/flann/CMakeFiles/opencv_test_flann.dir/build

modules/flann/CMakeFiles/opencv_test_flann.dir/clean:
	cd /d D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann && $(CMAKE_COMMAND) -P CMakeFiles\opencv_test_flann.dir\cmake_clean.cmake
.PHONY : modules/flann/CMakeFiles/opencv_test_flann.dir/clean

modules/flann/CMakeFiles/opencv_test_flann.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\git\github.com\opencv D:\git\github.com\opencv\modules\flann D:\git\github.com\Pixmatica\Build\OpenCV4 D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann D:\git\github.com\Pixmatica\Build\OpenCV4\modules\flann\CMakeFiles\opencv_test_flann.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : modules/flann/CMakeFiles/opencv_test_flann.dir/depend

