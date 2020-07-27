#include "cvMat.h"

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirXfr/Debug.h>

#include "cvSize.h"

cvMat::cvMat()
{

}

bool cvMat::set(const cv::Mat other)
{
    MUSTDO(it);
    return false;
}

void cvMat::clear()
{
    release();
    NEEDDO(size_etc)
}
