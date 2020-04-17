#include "Session.h"

#include <eirBase/Debug.h>

void Session::connect(const MultiName *name,
                      QObject *parent)
{
    TOUSE(name) TOUSE(parent) MUSTDO()
}

void Session::load(Uid sessionId, Uid resourceId)
{
    TOUSE(sessionId) TOUSE(resourceId) MUSTDO()
}

void Session::load(Uid sessionId, MultiName resourceName)
{
    TOUSE(sessionId) TOUSE(resourceName) MUSTDO()
}

void Session::unload(Uid sessionId, Uid resourceId)
{
    TOUSE(sessionId) TOUSE(resourceId) MUSTDO()
}

Uid Session::registerResource(MultiName name)
{
    TOUSE(name) MUSTDO()
}

void Session::disconnect(const Uid sessionId)
{
    TOUSE(sessionId) MUSTDO()
}

void Session::load(Uid resourceId)
{
    TOUSE(resourceId) MUSTDO()
}

void Session::load(MultiName resourceName)
{
    TOUSE(resourceName) MUSTDO()
}

void Session::unload(Uid resourceId)
{
    TOUSE(resourceId) MUSTDO()
}

Session::Session(QObject *parent)
    : QObject(parent)
{
    TRACEQOB(parent);
}
