#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

class cvRectStdVector
{
public:
    typedef std::vector<cv::Rect> CvRectStdVector;

public:
    cvRectStdVector();
    void set(const CvRectStdVector &rectVec);
    CvRectStdVector toCvRectStdVector() const;
    CvRectStdVector &toCvRectStdVector();

private:
    CvRectStdVector mCvRectStdVector;
}; // class cvRectStdVector

