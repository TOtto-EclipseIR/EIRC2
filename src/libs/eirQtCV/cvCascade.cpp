#include "cvCascade.h"

#include <eirXfr/Debug.h>

#include "cvString.h"

cvCascade::cvCascade(const BasicName &name)
{
    TRACEQFI << name();
    mName = name;
}

bool cvCascade::isLoaded() const
{
    return ! notLoaded();
}

bool cvCascade::notLoaded() const
{
    return mpCascade ? mpCascade->empty() : true;
}

bool cvCascade::load(const QFileInfo cascadeFI)
{
    TRACEQFI << cascadeFI;
    unload();
    cv::CascadeClassifier * cascade = new cv::CascadeClassifier();
    if (cascade->load(cvString(cascadeFI.filePath())))
    {
        mpCascade = cascade;
        mCascadeFileInfo = cascadeFI;
        NEEDDO(CoreSize);
    }
    return isLoaded();
}

void cvCascade::unload()
{
    TRACEQFI << mCascadeFileInfo;
    delete mpCascade;
    mpCascade=nullptr;
    mCascadeFileInfo = QFileInfo();
    mCoreSize = QSize();
    mInputImage = mFindRectImage = QImage();
    mFindRectMat.clear();
}
