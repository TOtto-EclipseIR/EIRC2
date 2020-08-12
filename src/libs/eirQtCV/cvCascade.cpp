#include "cvCascade.h"

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>

#include "cvString.h"

cvCascade::cvCascade(const BasicName &cascadeType)
{
    TRACEQFI << cascadeType();
    mCascadeType = cascadeType;
}

void cvCascade::dump(cvCascade::FindParameters parms,
                     const QSize inputSize)
{
    DUMP << mCascadeType();
    parms.calculate(inputSize, coreSize());
    DUMP << QString("%1 = %2 [%3]").arg("Factor").arg(parms.scaleFactor()).arg(parms.mFactor);

}

bool cvCascade::isLoaded() const
{
    return ! notLoaded();
}

bool cvCascade::notLoaded() const
{
    return mpCascade ? mpCascade->empty() : true;
}

QFileInfo cvCascade::fileInfo() const
{
    return mCascadeFileInfo;
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

QSize cvCascade::coreSize() const
{
    return mCoreSize;
}

bool cvCascade::setImage(const QImage &inputImage)
{
    TRACEQFI << inputImage.size() << inputImage.format();
    MUSTDO(it); MUSTDO(mFindRectImage);
    MUSTDO(mFindRectMat); MUSTUSE(inputImage);
    MUSTRTN(false);
    return false;
}

cvCascade::QRectList cvCascade::findRects(cvCascade::FindParameters parms)
{
    TRACEFN;
    MUSTUSE(parms);
    /*
    Classifier::detectMultiScale(
    InputArray 	image,
    std::vector< Rect > & 	objects,
    double 	scaleFactor = 1.1,
    int 	minNeighbors = 3,
    int 	flags = 0,
    Size 	minSize = Size(),
    Size 	maxSize = Size()
    )
    */
    TRACERTN(cvCascade::QRectList());
    return cvCascade::QRectList();
}

QImage cvCascade::findRectImage() const
{
    return mFindRectImage;
}

void cvCascade::FindParameters::calculate(const QSize inputSize, const QSize coreSize)
{
    TRACEQFI << inputSize << coreSize;
    MUSTDO(it); MUSTUSE(inputSize); MUSTUSE(coreSize);
}

double cvCascade::FindParameters::scaleFactor() const
{
    TRACEFN; MUSTDO(it); MUSTRTN(0.0);

}

int cvCascade::FindParameters::minNeighbors() const
{
    TRACEFN; MUSTDO(it); MUSTRTN(0);

}

int cvCascade::FindParameters::flags()
{
    TRACEFN; MUSTDO(it);  MUSTRTN(0);

}

cvCascade::MinMaxPair cvCascade::FindParameters::size() const
{
    TRACEFN; MUSTDO(it); MUSTRTN(MinMaxPair());

}
