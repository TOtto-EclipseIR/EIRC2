# CMake generated Testfile for 
# Source directory: D:/git/github.com/opencv/modules/imgcodecs
# Build directory: D:/git/github.com/Pixmatica/Build/OpenCV4/modules/imgcodecs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_imgcodecs "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_test_imgcodecs.exe" "--gtest_output=xml:opencv_test_imgcodecs.xml")
set_tests_properties(opencv_test_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Accuracy" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1282;ocv_add_test_from_target;D:/git/github.com/opencv/modules/imgcodecs/CMakeLists.txt;153;ocv_add_accuracy_tests;D:/git/github.com/opencv/modules/imgcodecs/CMakeLists.txt;0;")
add_test(opencv_perf_imgcodecs "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_perf_imgcodecs.exe" "--gtest_output=xml:opencv_perf_imgcodecs.xml")
set_tests_properties(opencv_perf_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Performance" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/performance" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1193;ocv_add_test_from_target;D:/git/github.com/opencv/modules/imgcodecs/CMakeLists.txt;157;ocv_add_perf_tests;D:/git/github.com/opencv/modules/imgcodecs/CMakeLists.txt;0;")
add_test(opencv_sanity_imgcodecs "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_perf_imgcodecs.exe" "--gtest_output=xml:opencv_perf_imgcodecs.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Sanity" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/sanity" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1194;ocv_add_test_from_target;D:/git/github.com/opencv/modules/imgcodecs/CMakeLists.txt;157;ocv_add_perf_tests;D:/git/github.com/opencv/modules/imgcodecs/CMakeLists.txt;0;")
