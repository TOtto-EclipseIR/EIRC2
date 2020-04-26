# file: {EIRC2 repo}./src/depends.pri

eirBase.subdir      = ./libs/eirBase
eirType.subdir      = ./libs/eirType
eirExe.subdir       = ./libs/eirExe
eirQtCV.subdir      = ./libs/eirQtCV
eirPixel.subdir     = ./libs/eirPixelImage

If2Console.subdir   = ./apps/cons/If2Console

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirPixel.depemds    = eirType
eirQtCV.depends     = eirBase eirType eirPixel
eirPixel.depemds    = eirType eirQtCV
If2Console.depends  = eirBase eirType eirExe eirPixel eirQtCV
