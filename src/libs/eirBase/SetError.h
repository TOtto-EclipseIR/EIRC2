// file: {EIRC2 repo}./src/lib/eirBase/SetError.h
#pragma once
#include "eirBase.h"

#include "ErrorHandler.h"

class EIRBASE_EXPORT SetError
{
public:
    SetError();
    bool isError() const;
    MultiName errorName() const;
    ErrorHandler::Item error() const;

protected:
    void clearError();
    void setError(const ErrorHandler::Item item);

private:
    ErrorHandler::Item mErrorItem;
};

