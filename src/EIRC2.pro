TEMPLATE = subdirs

include(./EIRC2.pri)

SUBDIRS += \
    ./libs/eirBase \
    ./libs/eirExe \
#    ./libs/eirPixelImage \
###    ./libs/eirResource \
###    ./libs/eirTask \
#    ./libs/eirQtCV4 \
    ./libs/eirType \
    ./libs/eirXfr \
    ./cons/If2Console \
 #   libs/eirHaar \
    cons/FaceConsole \
    libs/eirImage \ \
    libs/eirQtCV \
    libs/eirRectFind \
    libs/eirTask

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
#eirPixelImage.depends    = eirBase eirType
#eirQtCV.depends     = eirBase eirType eirXfr eirPixelImage
eirXfr.depends      = eirBase
eirImage.depends    = eirType eirExe
#eirHaar.depends     = eirBase eirType eirExe eirImage
#If2Console.depends  = eirBase eirType eirXfr eirExe eirHaar
If2Console.depends  = eirBase eirType eirXfr eirExe # eirHaar
