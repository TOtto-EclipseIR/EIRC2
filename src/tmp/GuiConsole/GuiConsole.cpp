#include "GuiConsole.h"

GuiConsole::GuiConsole(QWidget *parent)
    : QMainWindow(parent)
    , cmpMainLayout(new QGridLayout)
{
    Q_CHECK_PTR(cmpMainLayout);
}
