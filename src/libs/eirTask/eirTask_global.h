#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRTASK_LIBRARY)
#  define EIRTASK_EXPORT Q_DECL_EXPORT
#else
#  define EIRTASK_EXPORT Q_DECL_IMPORT
#endif
