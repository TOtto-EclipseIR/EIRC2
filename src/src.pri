# file: {EIRC2 repo}./src/src.pri

include(version.pri)
include(../ourbld.pri)
BASEDESTDIR = T:/bin
include(../ourdest.pri)
DESTDIR = $$OURDEST
LIBS *= -L$$OURDEST
include(depends.pri)

### TODO: Fix Bad Smell
include(./libs/eirQtCV4/OpenCV4.pri)

