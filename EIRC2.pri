# file: {EIRC2 repo}./EIRC2.pri

BASEDESTDIR = /bin
include(ourdest.pri)
DESTDIR = $$OURDEST

LIBS *= -L$$DESTDIR

