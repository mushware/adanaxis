#ifndef GAMESTL_H
#define GAMESTL_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameSTL.h,v 1.1 2003/02/05 17:36:36 southa Exp $
 * $Log: GameSTL.h,v $
 * Revision 1.1  2003/02/05 17:36:36  southa
 * Build fixes
 *
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
