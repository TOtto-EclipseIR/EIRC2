#pragma once

#include "ErrorHandler.h"

class SetError
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

