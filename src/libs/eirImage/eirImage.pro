#QT -= gui ### for QImage, etc.

TEMPLATE = lib
DEFINES += EIRIMAGE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../EIRC2.pri)
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirObjDet5
LIBS *= -leirQtCV5

SOURCES += \
    Hue.cpp \
    MarkManager.cpp \
    OutputManager.cpp \
    QQImage.cpp \
    SimpleRectMarker.cpp \
    eirImage.cpp

HEADERS += \
    Hue.h \
    MarkManager.h \
    OutputManager.h \
    QQImage.h \
    SimpleRectMarker.h \
    eirImage_global.h \
    eirImage.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
