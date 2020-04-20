# file: {EIRC2repo}./ourdest.pri

OURDEST = base/<bld><dbg>-<ver>
OURDEST = $$replace(OURDEST, base, $$BASEDESTDIR)
OURDEST = $$replace(OURDEST, <bld>, $$OURBLD)
CONFIG(debug, debug|release) {
    OURDEST = $$replace(OURDEST, <dbg>, dbg)
}
else {
    OURDEST = $$replace(OURDEST, <dbg>, bin)
}
OURDEST = $$replace(OURDEST, <ver>, $$EIRC2_VER_STRING)
message(OURDEST = $$OURDEST)
