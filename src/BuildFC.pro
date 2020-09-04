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
eirQtCV.depends     = eirExe eirType eirBase eirXfr
FaceConsole.depends = eirQtCV eirExe eirType eirBase eirXfr

