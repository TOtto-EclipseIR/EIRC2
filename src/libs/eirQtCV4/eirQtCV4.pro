###QT -= gui

TEMPLATE = lib
DEFINES += EIRQTCV4_LIBRARY

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

include(./OpenCV4.pri)
include(../libs.pri)

LIBS *= -leirBase2
LIBS *= -leirType2
LIBS *= -leirExe2

SOURCES += \
    Detector.cpp \
    HaarRectangles.cpp \
    ObjectType.cpp \
    QtCVcore.cpp \
    QtCVhighgui.cpp \
    QtCVimgproc.cpp \
    QtCVobjdetect.cpp \
    cvInputArray.cpp \
    cvRect.cpp \
    cvString.cpp \
    eirQtCV4.cpp

HEADERS += \
    Detector.h \
    HaarRectangles.h \
    ObjectType.h \
    QtCVcore.h \
    QtCVhighgui.h \
    QtCVimgproc.h \
    QtCVobjdetect.h \
    cvInputArray.h \
    cvRect.h \
    cvString.h \
    eirQtCV4_global.h \
    eirQtCV4.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    OpenCV4.pri