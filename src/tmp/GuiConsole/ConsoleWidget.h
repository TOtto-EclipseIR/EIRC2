#pragma once

#include <QWidget>
#include <QTextEdit>

class ConsoleWidget : public QTextEdit
{
    Q_OBJECT
public:
    enum Flag
    {
        NoFlag      = 0,
        Stdout      = 0x00000001,
        Stderr      = 0x00000002,
        QtDebug     = 0x00000004,
        Merged      = 0x00000008,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

public:
    explicit ConsoleWidget(QWidget *parent = nullptr);
    ConsoleWidget(const QString &text, const Flags flags, QWidget *parent = nullptr);

public slots:
    void setup(void);

signals:

private:
    Flags mFlags=NoFlag;
};

