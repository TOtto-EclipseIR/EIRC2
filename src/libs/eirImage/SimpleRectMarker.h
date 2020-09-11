#pragma once
#include "eirImage.h"

#include "QQImage.h"

#include <eirType/QQRectList.h>
#include <eirExe/Configuration.h>
#include <eirObjDet/ObjDetPak.h>

class EIRIMAGE_EXPORT SimpleRectMarker : public QQImage
{
public:
    SimpleRectMarker(const QQImage &inputImage);
    void mark(const Configuration &markRectConfig,
              const QQRectList &rectList,
              const ObjDetPak &pak);
};

