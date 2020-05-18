# file: {EIRC2 repo}./src/libs/eirQtCV/OpenCV.pri

OPENCV4BASEDIR = D:/git/github.com/EIRC2/3rd/OpenCV4

INCLUDEPATH *= OPENCV4BASEDIR\install\include
INCLUDEPATH *= OPENCV4BASEDIR
###INCLUDEPATH *= D:\git\github.com\OpenCV

LIBS *= -LOPENCV4BASEDIR\lib
LIBS *= -lopencv_core420
LIBS *= -lopencv_objdetect420

#LIBS *= D:\git\github.com\EIRC2\3rd\OpenCV4\lib\libopencv_core420.dll.a
#LIBS *= D:\git\github.com\EIRC2\3rd\OpenCV4\lib\libopencv_objdetect420.dll.a
