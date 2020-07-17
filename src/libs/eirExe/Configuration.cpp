#include "Configuration.h"


Configuration::Configuration() {;}
Configuration::Configuration(const VarMap &other) : VarMap(other) {;}

QString Configuration::string(const MultiName &key, const QString &defValue)
{
    QString strValue = at(key).value().toString();
    return strValue.isEmpty()
            ? defValue
            : strValue;
}

signed Configuration::signedInt(const MultiName &key, const signed &defValue)
{
    bool ok;
    signed sintValue = at(key).value().toInt(&ok);
    return  (ok & (sintValue != 0))
            ? sintValue
            : defValue;
}


