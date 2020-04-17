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
include(./OpenCV.pri)

LIBS *= -leirBase
LIBS *= -leirType
LIBS *= -leirExe

SOURCES += \
#    AbstractResource.cpp \
    HaarCascade.cpp \
#    HaarClassifier.cpp \
#    HaarDetector.cpp \
#    HaarRectangles.cpp \
    ObjectType.cpp \
    QtCVcore.cpp \
    QtCVhighgui.cpp \
    QtCVimgproc.cpp \
    QtCVobjdetect.cpp \
    QtOpenCV.cpp \
#    Session.cpp \
#    SessionManager.cpp \
    cvInputArray.cpp \
    cvString.cpp \
    eirQtCV.cpp

HEADERS += \
#    AbstractResource.h \
    HaarCascade.h \
#    HaarClassifier.h \
#    HaarDetector.h \
#    HaarRectangles.h \
    ObjectType.h \
    QtCVcore.h \
    QtCVhighgui.h \
    QtCVimgproc.h \
    QtCVobjdetect.h \
    QtOpenCV.h \
#    Session.h \
#    SessionManager.h \
    cvInputArray.h \
    cvString.h \
    eirQtCV_global.h \
    eirQtCV.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    OpenCV.pri
