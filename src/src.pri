# file: {EIRC2 repo}./src/src.pri

include(version.pri)
include(ourbld.pri)
BASEDESTDIR = T:/bin
include(ourdest.pri)
DESTDIR = $$OURDEST
LIBS *= -L$$OURDEST

#INCLUDEPATH *= ../eirBase

INCLUDEPATH *= ../../src/libs   # TODO: for apps
INCLUDEPATH *= ../../libs       # TODO: for libs

### TODO: Fix Bad Smell
include(../src/libs/eirQtCV4/OpenCV4.pri)

