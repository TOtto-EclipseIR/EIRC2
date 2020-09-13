TEMPLATE = subdirs

SUBDIRS += \
        ./libs/eirXfr \
        ./libs/eirBase \
        ./libs/eirType \
        ./libs/eirExe \
        ./libs/eirImage \
        ./libs/eirQtCV \
        ./libs/eirObjDet \
        ./cons/FaceConsole \

eirBase.depends     = eirXfr
eirType.depends     = eirBase eirXfr
eirExe.depends      = eirType eirBase ierXfr
eirQtCV.depends     = eirType eirBase eirExe eirXfr
eirObjDet.depends   = eirBase eirType eirExe eirObjDet
eirImage.depends    = eirType eirExe eirQtCV eirObjDet
FaceConsole.depends = eirQtCV eirExe eirType eirBase eirXfr

