/*
 * $Id$
 * $Log$
 */

#include "MustlStandard.h"


#if defined(HAVE_MUSHCORE_MUSHCORESINGLETON_H)
#include <Mushcore/MushcoreSingleton.h>
#else
#if defined(HAVE_MUSHCORESINGLETON_H)
#include <MushcoreSingleton.h>
#else
#include "MushcoreSingleton.h"
#endif
#endif
