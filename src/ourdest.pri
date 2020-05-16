# file: {EIRC2repo}./ourdest.pri

OURDEST = base/<bld><dbg>-<ver>
OURDEST = $$replace(OURDEST, base, $$BASEDESTDIR)
OURDEST = $$replace(OURDEST, <bld>, $$OURBLD)
CONFIG(debug, debug|release|profile) {
    OURDEST = $$replace(OURDEST, <dbg>, dbg)
}
#else {
#    OURDEST = $$replace(OURDEST, <dbg>, bin)
#}
CONFIG(release, debug|release|profile) {
    OURDEST = $$replace(OURDEST, <dbg>, bin)
}
CONFIG(profile, debug|release|profile) {
    OURDEST = $$replace(OURDEST, <dbg>, pro)
}
OURDEST = $$replace(OURDEST, <ver>, $$EIRC2_VER_STRING)

###message(OURDEST = $$OURDEST)
