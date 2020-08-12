#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRFRAME_LIBRARY)
#  define EIRFRAME_EXPORT Q_DECL_EXPORT
#else
#  define EIRFRAME_EXPORT Q_DECL_IMPORT
#endif
