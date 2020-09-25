#include "ConsoleWidget.h"

#include <QtDebug>

ConsoleWidget::ConsoleWidget(QWidget *parent)
    : QTextEdit(parent)
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("ConsoleWidget");
}

ConsoleWidget::ConsoleWidget(const QString &text, const Flags flags, QWidget *parent)
    : QTextEdit(text, parent)
    , mFlags(flags)
{
    qDebug() << Q_FUNC_INFO;
    switch (mFlags)
    {
    case Stdout:    setObjectName("ConsoleWidget:Stdout");      break;
    case Stderr:    setObjectName("ConsoleWidget:Stderr");      break;
    case QtDebug:   setObjectName("ConsoleWidget:QtDebug");     break;
    case Merged:    setObjectName("ConsoleWidget:Merged");      break;
    default:        setObjectName("ConsoleWidget");             break;
    }
}

void ConsoleWidget::setup()
{
    qDebug() << Q_FUNC_INFO;
    setReadOnly(true);
    setTabChangesFocus(true);
}
