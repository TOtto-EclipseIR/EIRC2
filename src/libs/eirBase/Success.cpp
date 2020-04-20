#include "Success.h"

Success::Success(void) : mSuccess(false) , mIsInitialized(false) {;}
Success::Success(const bool yes) : mSuccess(yes) , mIsInitialized(true) {;}

bool Success::set(const bool isTrue)
{
    mIsInitialized = true;
    mSuccess = isTrue;
    return  isTrue;
}

bool Success::is(void) const
{
    return mIsInitialized ? mSuccess : false;
}

bool Success::yes(void)
{
    set(true);
    return is();
}

bool Success::no(void)
{
    set(false);
    return is();
}

bool Success::expect(const bool isTrue)
{
    if (mIsInitialized) mSuccess &= isTrue;
    return is();
}

void Success::test(const bool isTrue)
{
    mIsInitialized = true;
    if ( ! isTrue)  mSuccess = false;
}

Success Success::tested(void)
{
    if ( ! mIsInitialized) mIsInitialized = mSuccess = true;
    return *this;
}

bool Success::isNull(void) const
{
    return ! mIsInitialized;
}

void Success::nullify(void)
{
    mIsInitialized = mSuccess = false;
}

Success::operator bool (void) const
{
    return is();
}

QString Success::toString(void) const
{
    return toString("OK", "FAIL", "UNKNOWN");
}

QString Success::toString(const QString & trueString,
                          const QString & falseString,
                          const QString & unknownString) const
{
    return isNull() ? unknownString
                    : is() ? trueString : falseString;
}