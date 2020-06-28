//! \file cvMat.h
#pragma once

#include <QFileInfo>
#include <QImage>

#include <QImage>
#include <QIODevice>

#include <opencv2/core/mat.hpp>

class cvMat
{
public:
    typedef cv::InputArray InputArray;

public:
    cvMat();
    cv::Mat mat() const;
    bool isEmpty() const;
    bool notEmpty() const;
    bool load(const QFileInfo &fileInfo);
    bool save(const QFileInfo &fileInfo);
    void set(const cv::Mat &other);
    QImage toImage(const QImage::Format qFormat=QImage::Format_ARGB32,
                   const QByteArray &mimeFormat="PNG");
    bool fromImage(const QImage &qImage,
                   const int cvMatType=0);
    int cols() const;
    int rows() const;

private:
    cv::Mat mCvMat;
};

