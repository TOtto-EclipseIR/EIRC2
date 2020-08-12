#include "SceneView.h"

#include "ImageScene.h"

SceneView::SceneView(ImageScene *scene)
    : QGraphicsView(scene, scene->widget())
{

}
