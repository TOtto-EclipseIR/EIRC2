# file: {EIRC2 repo}./src/src.pri

include(version.pri)
include(../ourbld.pri)
BASEDESTDIR = T:/bin
include(../ourdest.pri)
DESTDIR = $$OURDEST
LIBS *= -L$$OURDEST
include(depends.pri)


