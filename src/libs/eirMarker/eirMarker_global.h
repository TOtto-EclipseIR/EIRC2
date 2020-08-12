#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRMARKER_LIBRARY)
#  define EIRMARKER_EXPORT Q_DECL_EXPORT
#else
#  define EIRMARKER_EXPORT Q_DECL_IMPORT
#endif
