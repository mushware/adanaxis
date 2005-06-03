#ifndef GAMESTL_H
#define GAMESTL_H
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
 * $Id: GameSTL.h,v 1.1 2003/01/13 23:05:22 southa Exp $
 * $Log: GameSTL.h,v $
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSTL.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreSTL.h>
#else
#include "MushcoreSTL.h"
#endif
#endif
#endif
