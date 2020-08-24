# QT -= gui ### QImage

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

include(../../EIRC2.pri)
INCLUDEPATH *= $(QTCVINCLUDEPATH)
LIBS *= -L$(QTCVLIBPATH)
CONFIG(debug, debug|release) {
    LIBS *= -lopencv_world$(QTCVFILENAMEVER)d
    DISTFILES *= $(QTCVLIBPATH)/../bin/opencv_world$(QTCVFILENAMEVER)d.dll
} else {
    LIBS *= -lopencv_world$(QTCVFILENAMEVER)
    DISTFILES *= $(QTCVLIBPATH)/../bin/opencv_world$(QTCVFILENAMEVER).dll
}

PRE_TARGETDEPS *= $$OURDEST/eirCascade2.lib
PRE_TARGETDEPS *= $$OURDEST/eirQtCV2.lib
LIBS *= -leirCascade2
LIBS *= -leirQtCV2

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target