#pragma once

#include <QRgb>
#include <QVector>

class ColorTable
{
public:
    ColorTable(bool fillBlack=false);
    ColorTable(const QVector<QRgb> &other);
    QVector<QRgb> constColorVector() const;
    QVector<QRgb> &colorVector();
    bool isEmpty() const;
    void clear();
    void fill(const QRgb color=0, int count=-1);
    int colorCount() const;

private:
    QVector<QRgb> mColorVector;
};

