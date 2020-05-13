#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRRESOURCE_LIBRARY)
#  define EIRRESOURCE_EXPORT Q_DECL_EXPORT
#else
#  define EIRRESOURCE_EXPORT Q_DECL_IMPORT
#endif
