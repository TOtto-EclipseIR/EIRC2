#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRGRAPHICS_LIBRARY)
#  define EIRGRAPHICS_EXPORT Q_DECL_EXPORT
#else
#  define EIRGRAPHICS_EXPORT Q_DECL_IMPORT
#endif
