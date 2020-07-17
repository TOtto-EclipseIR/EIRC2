#include <QCoreApplication>

#include"FaceConsole.h"

#include "../../version.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("FaceConsole");
    a.setApplicationVersion(EIRC2_VER_STRING " " EIRC2_VER_TRUNKNAME);
    a.setOrganizationName(EIRC2_VER_ORGNAME);

    FaceConsole c(a.parent());
    Q_UNUSED(c);

    return a.exec();
}
