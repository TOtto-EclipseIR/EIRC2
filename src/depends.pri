# file: {EIRC2 repo}./src/depends.pri

eirBase.subdir      = ./libs/eirBase
eirType.subdir      = ./libs/eirType
eirExe.subdir       = ./libs/eirExe
eirQtCV.subdir      = ./libs/eirQtCV
eirPixel.subdir     = ./libs/eirPixelImage
eirXfr.subdir       = ./libs/eirXfr

If2Console.subdir   = ./apps/cons/If2Console

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirPixel.depemds    = eirBase eirType
eirQtCV.depends     = eirBase eirType eirXfr eirPixel
eirPixel.depemds    = eirType eirQtCV
eirXfr.depends      = eirBase eirType
If2Console.depends  = eirBase eirType eirXfr eirExe eirPixel eirQtCV
