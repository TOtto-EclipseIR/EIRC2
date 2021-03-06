#pragma once
#include "eirImage.h"

#include "QQImage.h"

#include <eirType/QQRectList.h>
#include <eirExe/Configuration.h>
#include <eirObjDet/ObjDetPak.h>
#include <eirObjDet/ObjDetResultList.h>

class EIRIMAGE_EXPORT SimpleRectMarker : public QQImage
{
public:
    SimpleRectMarker(const QQImage &inputImage);
    void markAll(const Configuration &markRectConfig,
                 const QQRectList &rectList);
    void mark(const Configuration &markRectConfig,
              const ObjDetResultList &resultList,
              const ObjDetPak &pak);
};

