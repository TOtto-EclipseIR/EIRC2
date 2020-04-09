# file: {EIRC2 repo}./src/depends.pri

eirBase.subdir      = ./libs/eirBase
eirType.subdir      = ./libs/eirType
eirExe.subdir       = ./libs/eirExe
eirQtCV.subdir      = ./libs/eirQtCV

If2Console.subdir   = ./apps/cons/If2Console

eirType.depends     = eirBase
eirExe.depends      = eirBase eirType
eirQtCV.depends     = eirBase eirType eitExe
If2Console.depends  = eirBase eirType eirExe eirQtCV
