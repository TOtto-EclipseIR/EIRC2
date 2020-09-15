#pragma once

#include <QWidget>
#include <QTextEdit>

class ConsoleWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = nullptr);

signals:

};

