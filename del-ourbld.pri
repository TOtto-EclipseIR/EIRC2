# file: {EIRC2repo}./ourbld.pri

OURBLD = "{???}"
windows:OURBLD = "windows"
win32:OURBLD = "win32"
win32-g++:contains(QMAKE_HOST.arch, x86_64):OURBLD = "win64"

unix:OURBLD = "unix"
linux-g++:OURBLD = "linux"
linux-g++:contains(QMAKE_HOST.arch, x86_64):OURBLD = "nix64"

message(OURBLD = $$OURBLD)
