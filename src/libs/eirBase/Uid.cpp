// file: {repo:EIRC2}./src/libs/eirType/Uid.cpp
#include "Uid.h"

#include <eirBase/Debug.h>

Uid::Uid(void) {;}
Uid::Uid(const QUuid quuid) { *this = quuid; }
Uid Uid::create() { return QUuid::createUuid(); }

