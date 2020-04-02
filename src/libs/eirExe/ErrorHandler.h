#pragma once
#include "eirExe.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QString>
#include <QStringList>

#include <eirBase/MultiName.h>
#include <eirBase/VarMap.h>
#include <eirType/Milliseconds.h>

class EIREXE_EXPORT ErrorHandler : public QObject
{
    Q_OBJECT

public:
    typedef uint Code;

    class EIREXE_EXPORT Item
    {
    public:
        Item();
        Item(const Code code,
             const VarMap & vars=VarMap());
        Item(const MultiName & name,
             const VarMap & vars=VarMap());
        QStringList messages() const;
        QString message(const QChar sep=QChar('\n')) const;
        bool debug() const;

        static uint registerCode(const MultiName & name,
                                 const QtMsgType qmt,
                                 const QString format,
                                 const VarMap & itemVars=VarMap());
        static bool isValid(const MultiName & name);
        static bool isValid(const Code code);
        bool isFatal() const;
        static Code registeredCode(const MultiName & name);
        static Item item(const MultiName & name);
        static Item item(const Code code);
        static void setFatal(const QtMsgType qmt);

    private:
        Milliseconds mMsec;
        Code mCode;
        MultiName mName;
        QtMsgType mMsgType;
        QString mFormat;
        VarMap mVars;
        VarMap mItemVars;
        static QHash<Code, Item> smCodeHash;
        static QtMsgType smFatalMsgType;
    };

public:
    explicit ErrorHandler();
    bool tryFileExist(const QString &fileName,
                      const QDir & dir=QDir());
    bool tryFileExist(const QFileInfo &fileInfo);

signals:

};

Q_GLOBAL_STATIC(ErrorHandler, error)

