# file: {EIRC2 repo}./EIRC2.pri

BASEDESTDIR = T:/bin # FAT32 Tmp Drive on Flash
include(ourdest.pri)
DESTDIR = $$OURDEST

LIBS *= -L$$DESTDIR

