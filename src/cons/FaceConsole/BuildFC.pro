TEMPLATE = subdirs

SUBDIRS += \
        ../../libs/eirXfr \
        ../../libs/eirBase \
        ../../libs/eirType \
        ../../libs/eirExe \
        ../../libs/eirFinder \
        ../../libs/eirQtCV \
        ../FaceConsole \
#        ../../libs/eirFrame \
#        ../../libs/eirMarker \
#        ../../libs/eirGraphics \
#        ../../libs/eirImageIO \


eirBase.depends     = eirXfr
eirType.depends     = eirBase eirXfr
eirExe.depends      = eirType eirBase ierXfr
eirFinder.depends   = eirExe eirType eirBase eirXfr
eirQtCV.depends     = eirFinder eirExe eirType eirBase eirXfr
FaceConsole.depends = eirQtCV eirFinder eirExe eirType eirBase eirXfr

#eirGraphics.depends = eirXfr
#eirMarker.depends   = eirBase eirXfr eirType eirFrame
