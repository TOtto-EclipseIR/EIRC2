#include "ImageScene.h"

#include <eirXfr/Debug.h>

ImageScene::ImageScene(QObject *parent)
    : QGraphicsScene(parent)
    , cmpFrame(new QFrame())
{
    TRACEFN;
    setObjectName("ImageScene");

}

QWidget *ImageScene::widget() const
{
    return (QWidget *)(cmpFrame);
}
