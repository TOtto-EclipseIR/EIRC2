QT -= gui

TEMPLATE = lib
DEFINES += EIRTYPE_LIBRARY

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

SOURCES += \
    Enumeration.cpp \
    QQRect.cpp \
    QQRectF.cpp \
    QQRectList.cpp \
    Region.cpp \
    Sortable.cpp \
    eirType.cpp

HEADERS += \
    Enumeration.h \
    EnumerationArray.h \
    EnumerationMask.h \
    Named.h \
    NamedArray.h \
    NamedEnum.h \
    NamedMap.h \
    QQRect.h \
    QQRectF.h \
    QQRectList.h \
    Region.h \
    Sortable.h \
    eirType_global.h \
    eirType.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
