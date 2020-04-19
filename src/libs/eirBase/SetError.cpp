#include "SetError.h"

SetError::SetError() {;}

bool SetError::isError() const
{
    return ! mErrorItem.isNull();
}

MultiName SetError::errorName() const
{
    return  mErrorItem.name();
}

ErrorHandler::Item SetError::error() const
{
    return mErrorItem;
}

void SetError::clearError()
{
    mErrorItem = ErrorHandler::Item();
}

void SetError::setError(const ErrorHandler::Item item)
{
    mErrorItem = item;
}
