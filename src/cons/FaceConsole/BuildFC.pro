TEMPLATE = subdirs

SUBDIRS += \
        ../../libs/eirXfr \
        ../../libs/eirBase \
        ../../libs/eirType \
        ../../libs/eirExe \
        ../../libs/eirCascade \
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
eirFinder.depends   = eirCascade eirExe eirType eirBase eirXfr
eirQtCV.depends     = eirFinder eirCascade eirExe eirType eirBase eirXfr
FaceConsole.depends = eirQtCV eirFinder eirCascade eirExe eirType eirBase eirXfr

#eirGraphics.depends = eirXfr
#eirMarker.depends   = eirBase eirXfr eirType eirFrame
