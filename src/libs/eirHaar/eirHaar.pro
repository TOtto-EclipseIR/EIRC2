QT += gui xml

TEMPLATE = lib
DEFINES += EIRHAAR_LIBRARY

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

include(../../EIRC2.pri)
include(./OpenCV.pri)

LIBS *= -leirBase2
LIBS *= -leirExe2

SOURCES += \
    HaarBase.cpp \
    HaarCascade.cpp \
    HaarCatalog.cpp \
    HaarDetector.cpp \
    cvCascade.cpp \
    cvString.cpp \
    cvVersion.cpp \
    eirHaar.cpp

HEADERS += \
    HaarBase.h \
    HaarCascade.h \
    HaarCatalog.h \
    HaarDetector.h \
    cvCascade.h \
    cvString.h \
    cvVersion.h \
    eirHaar_global.h \
    eirHaar.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../../../INDIface/detectors/Detectors.xml
