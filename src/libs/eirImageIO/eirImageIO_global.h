#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRIMAGEIO_LIBRARY)
#  define EIRIMAGEIO_EXPORT Q_DECL_EXPORT
#else
#  define EIRIMAGEIO_EXPORT Q_DECL_IMPORT
#endif
