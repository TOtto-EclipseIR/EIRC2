TEMPLATE = subdirs

SUBDIRS += \
        ../FaceConsole \
        ../../libs/eirBase \
        ../../libs/eirType \
        ../../libs/eirExe \
        ../../libs/eirXfr \
        ../../libs/eirFrame \
        ../../libs/eirMarker \
        ../../libs/eirGraphics \
        ../../libs/eirImageIO \
        ../../libs/eirQtCV \
        ../../libs/eirFinder \


eirType.depends     = eirBase eirXfr
eirQtCV.depends     = eirExe2
eirFinder.depends   = eirXfr eirType eirExe eirQtCV
eirGraphics.depends = eirXfr
eirMarker.depends   = eirBase eirXfr eirType eirFrame
FaceConsole.depends = eirBase eirXfr eirType eirExe eirFrame eirImageIO eirFinder eirGraphics
