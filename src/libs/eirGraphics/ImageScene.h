#pragma once

#include <QGraphicsScene>


#include <QFrame>

class ImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ImageScene(QObject * parent = nullptr);
    QWidget * widget() const;

private:
    QFrame const *cmpFrame=nullptr;
};

