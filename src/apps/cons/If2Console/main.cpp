#include <QCoreApplication>
#include "INDIfaceConsole.h"

#include "../../../../VERSION.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    INDIfaceConsole * c = new INDIfaceConsole();
    QTimer::singleShot(100, c, &INDIfaceConsole::initApplication);
    return a.exec();
}
