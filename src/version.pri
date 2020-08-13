# file: {EIRC2 repo}./src/version.pri

EIRC2_VER_MAJOR = 2
EIRC2_VER_MINOR = 9
EIRC2_VER_RELEASE = 2
EIRC2_VER_BRANCH = 44
EIRC2_VER_STRING = "v2.09B"
EIRC2_VER_TRUNKNAME = "develop"
EIRC2_VER_BRANCHNAME = "DebugStartup"
EIRC2_VER_QT = $${QT_VERSION}

windows:VERSION = 2.9.2.44
!windows:VERSION = 2.9.44
VER_MAJ = $${EIRC2_VER_MAJOR}
VER_MIN = $${EIRC2_VER_MINOR}
VER_PAT = $${EIRC2_VER_BRANCH}

#message("Version = $${EIRC2_VER_STRING}+$${EIRC_VER_BRANCHNAME} $${EIRC2_VER_TRUNKNAME}")
#message("QMAKESPEC = $${QMAKESPEC}")
