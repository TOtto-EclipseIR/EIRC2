#include "cvRectStdVector.h"

cvRectStdVector::cvRectStdVector() {;}

void cvRectStdVector::set(
    const cvRectStdVector::CvRectStdVector &rectVec)
{
    mCvRectStdVector = rectVec;
}

cvRectStdVector::CvRectStdVector
    cvRectStdVector::toCvRectStdVector() const
{
    return mCvRectStdVector;
}

cvRectStdVector::CvRectStdVector
    &cvRectStdVector::toCvRectStdVector()
{
    return mCvRectStdVector;
}


