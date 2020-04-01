# file: {EIRC2 repo}./EIRC2.pri

DESTDIR = /bin

win32 {
    CONFIG(debug, debug|release) {
        DESTDIR = /bin/win32d
    }
    else {
        DESTDIR = /bin/win32
    }
}

win64 {
    CONFIG(debug, debug|release) {
        DESTDIR = /bin/win64d
    }
    else {
        DESTDIR = /bin/win64
    }
}

LIBS *= -L$$DESTDIR

