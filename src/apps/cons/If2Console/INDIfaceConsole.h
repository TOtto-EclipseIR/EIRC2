#pragma once

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QList>

#include <eirExe/Console.h>
#include <eirQtCV/QtOpenCV.h>

class Settings;

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

protected:
    void startWork();
    int calculateScale(const QSize sz);
    QImage processImage(const QImage & inImage,
                        const int scale) const;

public slots:
    void initApplication();

private slots:
    void initResources();
    void initTaskLine();
    void startTaskLine();

    void process();
    void nextImage();

signals:
    void applicationInitd();
    void resoursesInitd();
    void taskLineInitd();
    void taskLineStarted();
    void processed();

private:
    QFileInfoList mPendingFiles;
    QDir mInputDir;
    QDir mOutputDir;

};

