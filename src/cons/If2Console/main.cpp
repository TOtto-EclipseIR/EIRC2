// file: {EIRC2 repo}./src/cons/If2Console/main.cpp

#include <QCoreApplication>
#include "INDIfaceConsole.h"

#include "../../version.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    INDIfaceConsole * c = new INDIfaceConsole();
    QTimer::singleShot(100, c, &INDIfaceConsole::initializeApplication);
    return a.exec();
}
