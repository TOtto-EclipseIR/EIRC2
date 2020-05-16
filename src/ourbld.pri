# file: {EIRC2repo}./ourbld.pri

OURBLD = "{???}"
windows:OURBLD = "windows"
win32:OURBLD = "win32"
win32-g++:contains(QMAKE_HOST.arch, x86_64):{
    OURBLD = "win64"
} else {
    OURBLD = "win32"
}

#message(OURBLD = $$OURBLD)
