#ifndef MUSTLMUSHCORESINGLETON_H
#define MUSTLMUSHCORESINGLETON_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlMushcoreSingleton.h,v 1.1 2003/01/20 10:45:30 southa Exp $
 * $Log: MustlMushcoreSingleton.h,v $
 * Revision 1.1  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
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
#endif
