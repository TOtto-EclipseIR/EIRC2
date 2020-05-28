#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRHAAR_LIBRARY)
#  define EIRHAAR_EXPORT Q_DECL_EXPORT
#else
#  define EIRHAAR_EXPORT Q_DECL_IMPORT
#endif
