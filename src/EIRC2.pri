# file: {EIRC2 repo}./src/EIRC2.pri

#ENV_QT4INCLUDEBASE = $$(QT4INCLUDEBASE)

message(QT4INCLUDEBASE = $$(QT4INCLUDEBASE))
#message(ENV_QT4INCLUDEBASE = $$ENV_QT4INCLUDEBASE)
message(QTBASEDESTDIR = $$(QTBASEDESTDIR))
message(QTCVINCLUDEPATH = $$(QTCVINCLUDEPATH))
#message(PATH = $$(PATH))

include(version.pri)
include(ourbld.pri)
#BASEDESTDIR = T:/bin
include(ourdest.pri)
DESTDIR = $$OURDEST
LIBS *= -L$$OURDEST
include(ipath.pri)

### TODO: Fix Bad Smell
#include(./libs/eirQtCV4/OpenCV4.pri)

