# CMake generated Testfile for 
# Source directory: D:/git/github.com/opencv/modules/dnn
# Build directory: D:/git/github.com/Pixmatica/Build/OpenCV4/modules/dnn
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_dnn "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_test_dnn.exe" "--gtest_output=xml:opencv_test_dnn.xml")
set_tests_properties(opencv_test_dnn PROPERTIES  LABELS "Main;opencv_dnn;Accuracy" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1282;ocv_add_test_from_target;D:/git/github.com/opencv/modules/dnn/CMakeLists.txt;126;ocv_add_accuracy_tests;D:/git/github.com/opencv/modules/dnn/CMakeLists.txt;0;")
add_test(opencv_perf_dnn "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_perf_dnn.exe" "--gtest_output=xml:opencv_perf_dnn.xml")
set_tests_properties(opencv_perf_dnn PROPERTIES  LABELS "Main;opencv_dnn;Performance" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/performance" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1193;ocv_add_test_from_target;D:/git/github.com/opencv/modules/dnn/CMakeLists.txt;131;ocv_add_perf_tests;D:/git/github.com/opencv/modules/dnn/CMakeLists.txt;0;")
add_test(opencv_sanity_dnn "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_perf_dnn.exe" "--gtest_output=xml:opencv_perf_dnn.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_dnn PROPERTIES  LABELS "Main;opencv_dnn;Sanity" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/sanity" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1194;ocv_add_test_from_target;D:/git/github.com/opencv/modules/dnn/CMakeLists.txt;131;ocv_add_perf_tests;D:/git/github.com/opencv/modules/dnn/CMakeLists.txt;0;")
