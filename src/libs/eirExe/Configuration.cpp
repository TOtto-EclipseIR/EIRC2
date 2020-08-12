#include "Configuration.h"


Configuration::Configuration() {;}
Configuration::Configuration(const VarMap &other) : VarMap(other) {;}

QString Configuration::string(const MultiName &key, const QString &defValue) const
{
    QString strValue = value(key).value().toString();
    return notContains(key)
            ? defValue
            : strValue;
}

signed Configuration::signedInt(const MultiName &key, const signed defValue) const
{
    bool ok;
    signed sintValue = value(key).value().toInt(&ok);
    return  (ok && contains(key))
            ? sintValue
            : defValue;
}

unsigned Configuration::unsignedInt(const MultiName &key, const unsigned defValue) const
{
    bool ok;
    unsigned uintValue = value(key).value().toUInt(&ok);
    return  (ok && contains(key))
            ? uintValue
            : defValue;
}

bool Configuration::boolean(const MultiName &key, const bool defValue) const
{
    bool boolValue = value(key).value().toBool();
    return notContains(key)
            ? defValue
            : boolValue;
}

qreal Configuration::real(const MultiName &key, const qreal &defValue) const
{
    bool ok;
    bool realValue = value(key).value().toDouble(&ok);
    return  (ok && contains(key))
            ? realValue
            : defValue;
}


