#include <QCoreApplication>
#include "INDIfaceConsole.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    INDIfaceConsole c;
    QTimer::singleShot(100, &c, &INDIfaceConsole::run);
    return a.exec();
}
