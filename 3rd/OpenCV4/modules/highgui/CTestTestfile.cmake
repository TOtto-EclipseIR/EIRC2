# CMake generated Testfile for 
# Source directory: D:/git/github.com/opencv/modules/highgui
# Build directory: D:/git/github.com/Pixmatica/Build/OpenCV4/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_test_highgui.exe" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1282;ocv_add_test_from_target;D:/git/github.com/opencv/modules/highgui/CMakeLists.txt;165;ocv_add_accuracy_tests;D:/git/github.com/opencv/modules/highgui/CMakeLists.txt;0;")
