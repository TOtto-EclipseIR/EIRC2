# file: {EIRC2 repo}./src/depends.pri

#eirBase.subdir      = ./libs/eirBase
#eirType.subdir      = ./libs/eirType
#eirExe.subdir       = ./libs/eirExe
#eirQtCV.subdir      = ./libs/eirQtCV
#eirPixel.subdir     = ./libs/eirPixelImage
#eirXfr.subdir       = ./libs/eirXfr

#If2Console.subdir   = ./cons/If2Console

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirXfr.depends      = eirBase eirType
eirPixel.depends    = eirBase eirType
eirQtCV.depends     = eirBase eirType eirXfr eirPixel
eirPixelImage.depends    = eirBase eirType
#eirPixelImage.depends    = eirQtCV
If2Console.depends  = eirBase eirType eirXfr eirExe eirPixel eirQtCV
