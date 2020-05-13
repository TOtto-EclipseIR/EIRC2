# CMake generated Testfile for 
# Source directory: D:/git/github.com/opencv/modules/video
# Build directory: D:/git/github.com/Pixmatica/Build/OpenCV4/modules/video
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_video "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_test_video.exe" "--gtest_output=xml:opencv_test_video.xml")
set_tests_properties(opencv_test_video PROPERTIES  LABELS "Main;opencv_video;Accuracy" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1282;ocv_add_test_from_target;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1073;ocv_add_accuracy_tests;D:/git/github.com/opencv/modules/video/CMakeLists.txt;2;ocv_define_module;D:/git/github.com/opencv/modules/video/CMakeLists.txt;0;")
add_test(opencv_perf_video "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_perf_video.exe" "--gtest_output=xml:opencv_perf_video.xml")
set_tests_properties(opencv_perf_video PROPERTIES  LABELS "Main;opencv_video;Performance" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/performance" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1193;ocv_add_test_from_target;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1074;ocv_add_perf_tests;D:/git/github.com/opencv/modules/video/CMakeLists.txt;2;ocv_define_module;D:/git/github.com/opencv/modules/video/CMakeLists.txt;0;")
add_test(opencv_sanity_video "D:/git/github.com/Pixmatica/Build/OpenCV4/bin/opencv_perf_video.exe" "--gtest_output=xml:opencv_perf_video.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_video PROPERTIES  LABELS "Main;opencv_video;Sanity" WORKING_DIRECTORY "D:/git/github.com/Pixmatica/Build/OpenCV4/test-reports/sanity" _BACKTRACE_TRIPLES "D:/git/github.com/opencv/cmake/OpenCVUtils.cmake;1640;add_test;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1194;ocv_add_test_from_target;D:/git/github.com/opencv/cmake/OpenCVModule.cmake;1074;ocv_add_perf_tests;D:/git/github.com/opencv/modules/video/CMakeLists.txt;2;ocv_define_module;D:/git/github.com/opencv/modules/video/CMakeLists.txt;0;")
