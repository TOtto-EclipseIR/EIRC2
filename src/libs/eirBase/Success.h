#pragma once
#include "eirBase.h"

#include <QString>

class EIRBASE_EXPORT Success
{
public:
    Success(void);
    Success(const bool yes);
    bool set(const bool isTrue=true);
    bool is(void) const;
    bool yes(void);
    bool no(void);
    bool expect(const bool isTrue);
    void test(const bool isTrue);
    bool isNull(void) const;
    void nullify(void);
    Success tested(void);
    operator bool (void) const;
    QString toString(void) const;
    QString toString(const QString & trueString,
                     const QString & falseString,
                     const QString & unknownString) const;

private:
    bool mSuccess = false;
    bool mIsInitialized = false;
};


