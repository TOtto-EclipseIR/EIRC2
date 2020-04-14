#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRPIXELIMAGE_LIBRARY)
#  define EIRPIXELIMAGE_EXPORT Q_DECL_EXPORT
#else
#  define EIRPIXELIMAGE_EXPORT Q_DECL_IMPORT
#endif
