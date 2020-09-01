#pragma once

#include <QList>
#include <QPair>

#include <eirType/MultiName.h>
#include <eirXfr/Debug.h>

typedef QPair<MultiName, int /*QGraphics Layer*/> NamedLayer;
typedef QList <NamedLayer> NamedLayerList;
typedef QMap<MultiName, int> NamedLayerMap;

class MarkerTypes
{
public:
    MarkerTypes();
};

