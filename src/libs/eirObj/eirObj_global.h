#pragma once

#include <QtCore/qglobal.h>

#if defined(EIROBJ_LIBRARY)
#  define EIROBJ_EXPORT Q_DECL_EXPORT
#else
#  define EIROBJ_EXPORT Q_DECL_IMPORT
#endif
