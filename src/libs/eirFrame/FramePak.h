// file: {repo: EIRC2}./src/libs/eirFrame/FramePak.h
#pragma once
#include "eirFrame.h"

#include <eirType/ValuePak.h>

#include "Frame.h"

class EIRFRAME_EXPORT FramePak : public ValuePak
{
public:
    FramePak();
    Frame frame() const;
    Frame face(const int index) const;
    QString toString() const;
    QString operator()() const;

protected:
    Frame frameAt(const int index) const;
    Frame toFrame(const QImage &image) const;
};

