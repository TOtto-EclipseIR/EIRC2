#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRQTCV4_LIBRARY)
#  define EIRQTCV4_EXPORT Q_DECL_EXPORT
#else
#  define EIRQTCV4_EXPORT Q_DECL_IMPORT
#endif
