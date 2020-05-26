#QT -= gui ### get QImage back

CONFIG += c++17 console
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


###target = If2Console
###depends = eirExe

include(../../EIRC2.pri)

LIBS *= -leirBase2
LIBS *= -leirType2
LIBS *= -leirImage2
LIBS *= -leirExe2
LIBS *= -leirHaar2
#LIBS *= -leirQtCV42

SOURCES += \
        INDIfaceConsole.cpp \
    If2CommandLine.cpp \
        main.cpp \

HEADERS += \
    ../../version.h \
    INDIfaceConsole.h \
    If2CommandLine.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../../../INDIface/detectors/Detectors.xml \
    DetectCascades.txt \
    DetectRD.txt \
    Input01.txt \
    OutputRD.txt \
