# file: {EIRC2repo}./src/opencv4.pri

#INCLUDEPATH *= F:/lang/OpenCV4/opencv/build/include
INCLUDEPATH *= $(QTCVINCLUDEPATH)
#LIBS *=      -LF:\lang\OpenCV4\opencv\build\x64\vc15\lib

CONFIG(debug, debug|release) {
#    LIBS *= -lopencv_world430d
    LIBS *= F:\lang\OpenCV4\opencv\build\x64\vc15\lib\opencv_world430d.lib
} else {
#    LIBS *= -lopencv_world430
    LIBS *= F:\lang\OpenCV4\opencv\build\x64\vc15\lib\opencv_world430.lib
}
message(INCLUDEPATH = $${INCLUDEPATH})
#message(LIBS = $${LIBS})
