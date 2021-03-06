#QT -= gui # QImage
Qt *= xml

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = INDI5console
RC_FILE = INDI5console.rc

include(../../EIRC2.pri)
include(../../opencv4.pri)

LIBS *= -leirXfr5
LIBS *= -leirBase5
LIBS *= -leirType5
LIBS *= -leirExe5
LIBS *= -leirImage5
LIBS *= -leirObjDet5
LIBS *= -leirQtCV5

SOURCES += \
    FaceConsole.cpp \
    main.cpp

HEADERS += \
    ../../version.h \
    FaceConsole.h \
    INDI5console.rc

DISTFILES += \
    ../../../../../bin/config/DetectCascades.txt \
    ../../../../../bin/config/DetectRD.txt \
    ../../../../../bin/config/I5c.bat \
    ../../../../../bin/config/Input01.txt \
    ../../../../../bin/config/OutputRD.txt \
    ../../../../../bin/config/SkyPlex.txt \
    ../../../../../bin/config/fodder.txt \
    ../../../../../bin/detectors/v2/Aim8A001-32-NoSplit.xml \
    ../../../../../bin/detectors/v4/haarcascade_frontalface_default.xml \
    I5c.bat \
    INDIface24.ico \
    Notes.txt \
    T:/bin/DetectCascades.txt \
    T:/bin/DetectRD.txt \
    T:/bin/Input01.txt \
    T:/bin/OutputRD.txt


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

