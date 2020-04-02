# file: {EIRC2 repo}./EIRC2.pri

DESTDIR = /bin

win32 {
    CONFIG(debug, debug|release) {
        DESTDIR = /INDIface/win32d
    }
    else {
        DESTDIR = /INDIface/win32
    }
}

win64 {
    CONFIG(debug, debug|release) {
        DESTDIR = /INDIface/win64d
    }
    else {
        DESTDIR = /INDIface/win64
    }
}

LIBS *= -L$$DESTDIR

