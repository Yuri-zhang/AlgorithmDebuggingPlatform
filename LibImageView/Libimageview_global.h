#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TESTIMAGEVIEW_LIB_LIB)
#  define TESTIMAGEVIEW_LIB_EXPORT Q_DECL_EXPORT
# else
#  define TESTIMAGEVIEW_LIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define TEST_IMAGEVIEW_LIB_EXPORT
#endif
