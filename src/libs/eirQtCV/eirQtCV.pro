#QT -= gui ## for QImage

TEMPLATE = lib
DEFINES += EIRQTCV_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../libs.pri)

INCLUDEPATH *= D:\git\github.com\EIRC2\src\3rd\OpenCV4\install\include
INCLUDEPATH *= D:\git\github.com\EIRC2\src\3rd\OpenCV4

LIBS *= -LD:\git\github.com\EIRC2\src\3rd\OpenCV4\lib
LIBS *= -lopencv_objdetect420

LIBS *= -leirBase
LIBS *= -leirType
LIBS *= -leirExe

SOURCES += \
    Configurations.cpp \
    HaarCascade.cpp \
    QtOpenCV.cpp \
    cvInputArray.cpp \
    cvString.cpp \
    eirQtCV.cpp

HEADERS += \
    Configurations.h \
    HaarCascade.h \
    QtOpenCV.h \
    cvInputArray.h \
    cvString.h \
    eirQtCV_global.h \
    eirQtCV.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
