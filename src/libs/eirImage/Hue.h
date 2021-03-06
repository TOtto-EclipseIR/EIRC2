#pragma once

#include <eirType/Rational.h>

class Hue : public Rational
{
public:
    Hue();
    Hue(const int threesixty);
    Hue(const qreal tworadians);
    Hue(const quint8 twofiftyfive);

public: // static
    static Hue white;
    static Hue black;
    static Hue red;
    static Hue blue;
    static Hue green;
    static Hue magenta;
    static Hue cyan;
    static Hue yellow;

};

