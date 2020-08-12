#pragma once

#include <QGraphicsView>

class ImageScene;

class SceneView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SceneView(ImageScene *scene = nullptr);

signals:

private:
    ImageScene * cmpScene=nullptr;
};

