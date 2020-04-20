QT -= gui

TEMPLATE = lib
DEFINES += EIRBASE_LIBRARY

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

SOURCES += \
    BasicName.cpp \
    ErrorHandler.cpp \
    Id.cpp \
    Milliseconds.cpp \
    MultiName.cpp \
    MultiNameMap.cpp \
    SetError.cpp \
    Success.cpp \
    UInt128.cpp \
    Uid.cpp \
    Var.cpp \
    VarMap.cpp \
    VarMapMap.cpp \
    VarPak.cpp \
    VersionInfo.cpp \
    eirBase.cpp

HEADERS += \
    ../../../VERSION.h \
    BasicName.h \
    Debug.h \
    ErrorHandler.h \
    Id.h \
    Milliseconds.h \
    MultiName.h \
    MultiNameMap.h \
    SetError.h \
    Success.h \
    UInt128.h \
    Uid.h \
    Var.h \
    VarMap.h \
    VarMapMap.h \
    VarPak.h \
    VersionInfo.h \
    eirBase_global.h \
    eirBase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../depends.pri \
    ../../../ourdest.pri \
    ../../apps/apps.pri \
    ../../apps/cons/cons.pri \
    ../../depends.pri