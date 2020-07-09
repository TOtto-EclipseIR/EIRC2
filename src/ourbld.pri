# file: {EIRC2repo}./ourbld.pri

OURBLD = "{???}"
win32:OURBLD = "win32"
win64:OURBLD = "win64"
win32-g++:OURBLD = "win32-g++"
win64-g++:OURBLD = "win64-g++"
win32-msvc:OURBLD = "win32-msvc"
win64-msvc:OURBLD = "win64-msvc"
message(OURBLD = $$OURBLD)
message(QMAKESPEC = $$QMAKESPEC)
