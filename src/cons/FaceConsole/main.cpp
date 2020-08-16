#include <QCoreApplication>

#include"FaceConsole.h"

#include "../../version.h"

#include <QtGlobal>
#include <QtDebug>
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTimer>

//#include <eirXfr/StartupDebug.h>

int main(int argc, char *argv[])
{
    //StartupDebug slog(argv[0]);

    QCoreApplication a(argc, argv);
    a.setApplicationName("INDI5faceConsole");
    a.setApplicationVersion(EIRC2_VER_STRING " " EIRC2_VER_TRUNKNAME);
    a.setOrganizationName(EIRC2_VER_ORGNAME);

    FaceConsole c(a.parent());
    Q_UNUSED(c);

    return a.exec();
}
