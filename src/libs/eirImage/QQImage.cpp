#include "QQImage.h"

QQImage::QQImage() {;}
QQImage::QQImage(const QImage &other) : QImage(other) {;}
QQImage::QQImage(const QString &fileName, const char *format) : QImage(fileName, format) {;}


