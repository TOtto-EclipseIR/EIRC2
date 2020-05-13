#include "qImage.h"

qImage::qImage() {;}

qImage::qImage(const QImage &img) : QImage(img) {;}

void qImage::set(const QImage &img)
{
    *this = img;
}

cvMat qImage::toCVMat() const
{
//    cvMat mat()
}
