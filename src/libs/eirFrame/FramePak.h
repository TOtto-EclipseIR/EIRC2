// file: {repo: EIRC2}./src/libs/eirFrame/FramePak.h
#pragma once
#include "eirFrame.h"

#include <eirType/QQRectList.h>
#include <eirType/ValuePak.h>

#include "Frame.h"

class EIRFRAME_EXPORT FramePak : public ValuePak
{
public:
    FramePak();
    FramePak(const QString &inputFileName);
    Frame frame() const;
    Frame face(const int index) const;
    QString toString() const;
    QString operator()() const;
    bool setInputFrame(const QString &inputFileName);
    bool setInputFrame(const QFileInfo &inputFileInfo);
    void setPreScanImage(const QImage &detectImage);
    void setFrameRectangles(const QList<QRect> &rects);

protected:
    Frame frameAt(const int index) const;
    Frame toFrame(const QImage &image) const;
};

