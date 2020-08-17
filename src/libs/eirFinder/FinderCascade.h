#pragma once

#include <eirExe/ConfigObject.h>
#include <eirQtCV/cvCascade.h>

class FinderCascade
{
public:
    typedef MinMaxPair<QSize> MinMaxSizePair;
public:
    FinderCascade(const CascadeType &cascadeType,
                  ConfigObject *configObject);
    const ConfigObject *config() const;
    const cvCascade cascade() const;
    cvCascade &cascade();
    void clear();
    bool setImage(const QImage &inputImage);
    bool findRectangles();
    cvCascade::RectList rectList() const;
    QImage findRectImage() const;

private:
    const CascadeType cmCascadeType;
    const ConfigObject *cmpCfgObj=nullptr;
    cvCascade mCascade;
    QImage mInputImage;
    QImage mFindRectImage;
    cvMat mFindRectMat;
    cvCascade::RectList mRectList;
};

