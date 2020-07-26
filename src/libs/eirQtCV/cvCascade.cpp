#include "cvCascade.h"

#include <eirXfr/Debug.h>

cvCascade::cvCascade()
{
    TRACEFN;
}

cvCascade::~cvCascade()
{
    TRACEFN;
    unload();
}

bool cvCascade::load(const QFileInfo cascadeFI)
{
    TRACEQFI << cascadeFI;
    NEEDDO(it);
    return false;
}

void cvCascade::unload()
{
    load(QFileInfo());
}
