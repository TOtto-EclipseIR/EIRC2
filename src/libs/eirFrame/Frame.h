// file: {repo: EIRC2}./src/libs/eirFrame/Frame.h
#pragma once
#include "eirFrame.h"

#include <QImage>

#include <QFileInfo>

class EIRFRAME_EXPORT Frame : public QImage
{
public:
    Frame(const QFileInfo fileInfo);
    Frame(const QFileInfo fileInfo,
          const QImage image);
    void set(const QImage &image);
    void set(const QFileInfo &fileInfo);
    QFileInfo fileInfo() const;
};

