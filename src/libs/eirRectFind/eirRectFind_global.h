#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRRECTFIND_LIBRARY)
#  define EIRRECTFIND_EXPORT Q_DECL_EXPORT
#else
#  define EIRRECTFIND_EXPORT Q_DECL_IMPORT
#endif
