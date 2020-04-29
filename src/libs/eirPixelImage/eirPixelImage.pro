# file: {repo: EIRC2}./src/libs/eirPixelImage/exePixelImage.pro
#QT -= gui ### Need QImage, etc.

TEMPLATE = lib
DEFINES += EIRPIXELIMAGE_LIBRARY

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

LIBS *= -leirBase2
LIBS *= -leirType2

SOURCES += \
    AbstractImageInterface.cpp \
    BaseDeviation.cpp \
    BaseImage.cpp \
    ColorImage.cpp \
    DeviationImage.cpp \
    GreyAverageImage.cpp \
    GreyImage.cpp \
    GreySelfDeviation.cpp \
    Image.cpp \
    ImageClass.cpp \
    ImageMarker.cpp \
    ImagePak.cpp \
    ImageType.cpp \
    cvFormat.cpp \
    eirPixelImage.cpp \
    qiFormat.cpp \
    qvfFormat.cpp

HEADERS += \
    AbstractImageInterface.h \
    BaseDeviation.h \
    BaseImage.h \
    ColorImage.h \
    DeviationImage.h \
    GreyAverageImage.h \
    GreyImage.h \
    GreySelfDeviation.h \
    Image.h \
    ImageClass.h \
    ImageMarker.h \
    ImagePak.h \
    ImageType.h \
    cvFormat.h \
    eirPixelImage_global.h \
    eirPixelImage.h \
    qiFormat.h \
    qvfFormat.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
