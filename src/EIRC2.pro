TEMPLATE = subdirs

include(./EIRC2.pri)

SUBDIRS += \
    ./libs/eirBase \
    ./libs/eirExe \
    ./libs/eirQtCV \
    ./libs/eirType \
    ./libs/eirXfr \
    ./cons/If2Console \
    ./cons/FaceConsole \ \
    eirFrame \
    libs/eirFinder \
    libs/eirImageIO

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirQtCV.depends     = eirBase eirType eirXfr
eirXfr.depends      = eirBase
