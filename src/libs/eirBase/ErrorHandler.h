#pragma once
#include "eirBase.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QString>
#include <QStringList>

//#include <eirBase/MultiName.h>
#include <eirBase/VarMap.h>
#include <eirBase/Milliseconds.h>

#include "../../libs/eirBase/MultiName.h"

class EIRBASE_EXPORT ErrorHandler : public QObject
{
    Q_OBJECT

public:
    typedef uint Code;

    class EIRBASE_EXPORT Item
    {
    public:
        Item();
        Item(const Code code,
             const VarMap & vars=VarMap());
        Item(const MultiName & name,
             const VarMap & vars=VarMap());
        bool isNull() const;
        void setVars(const VarMap &vars);
        MultiName name() const;
        QStringList messages() const;
        QString message(const QChar sep=QChar('\n')) const;
        bool debug() const;

        static Code registerCode(const MultiName & name,
                                 const QtMsgType qmt,
                                 const QString format,
                                 const VarMap & itemVars=VarMap());
        static Var::List registerCodes(const VarMap::List maps);
        static bool isValid(const MultiName & name);
        static bool isValid(const Code code);
        bool isFatal() const;
        bool notError() const;
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
    bool submit(const Item item, const bool fail=true);
    bool submit(const Code code, const VarMap & vars, const bool fail=true);
    bool submit(const MultiName &name, const VarMap & vars, const bool fail=true);
    Item test(const bool is,
                const QString & what=QString(),
                Item item=Item());
    bool expect(const bool is,
                const QString & what=QString(),
                Item item=Item());

    bool tryFileMode(const QIODevice::OpenMode mode,
                      const QString &fileName,
                     const QString & what=QString(),
                      const QDir & dir=QDir());
    bool tryFileMode(const QIODevice::OpenMode mode,
                     QFile * file,
                     const QString & what=QString());
    bool tryFileMode(const QIODevice::OpenMode mode,
                     const QFileInfo &fileInfo,
                     const QString & what=QString());

private slots:
    void registerCodes();

signals:
    void triggered(Item item);
    void triggered(QString message);
    void triggered(QStringList messages);

};

Q_GLOBAL_STATIC(ErrorHandler, errorHandler)

