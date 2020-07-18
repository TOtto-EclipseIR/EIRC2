TEMPLATE = subdirs

include(./EIRC2.pri)

SUBDIRS += \
    ./libs/eirBase \
    ./libs/eirExe \
    ./libs/eirResource \
    ./libs/eirTask \
    ./libs/eirQtCV4 \
    ./libs/eirType \
    ./libs/eirXfr \
    ./cons/If2Console \
    cons/FaceConsole \
    libs/eirImage \
    libs/eirRectFind \

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirQtCV4.depends     = eirBase eirType eirXfr
eirXfr.depends      = eirBase
eirImage.depends    = eirType eirExe
If2Console.depends  = eirBase eirType eirXfr eirExe
