#ifndef GLSTL_H
#define GLSTL_H
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
 * $Id: GLSTL.h,v 1.1 2003/01/13 14:31:55 southa Exp $
 * $Log: GLSTL.h,v $
 * Revision 1.1  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORESTL_H)
#include <Mushcore/MushcoreSTL.h>
#else
#if defined(HAVE_MUSHCORESTL_H)
#include <MushcoreSTL.h>
#else
#include "MushcoreSTL.h"
#endif
#endif
#endif
