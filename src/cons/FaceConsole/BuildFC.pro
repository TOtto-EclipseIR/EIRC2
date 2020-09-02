TEMPLATE = subdirs

SUBDIRS += \
    ../../libs/eirObjDet \
        ../../libs/eirXfr \
        ../../libs/eirBase \
        ../../libs/eirType \
        ../../libs/eirExe \
        ../../libs/eirCascade \
        ../../libs/eirImage \
        ../../libs/eirQtCV \
        ../../libs/eirObjDet \
        ../FaceConsole \

eirBase.depends     = eirXfr
eirType.depends     = eirBase eirXfr
eirExe.depends      = eirType eirBase ierXfr
eirCascade.depends  = eirType
eirQtCV.depends     = eirCascade eirExe eirType eirBase eirXfr
FaceConsole.depends = eirQtCV eirCascade eirExe eirType eirBase eirXfr

