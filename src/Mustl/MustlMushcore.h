#ifndef MUSTLMUSHCORE_H
#define MUSTLMUSHCORE_H
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
 * $Id: MustlMushcore.h,v 1.1 2003/01/13 15:01:20 southa Exp $
 * $Log: MustlMushcore.h,v $
 * Revision 1.1  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 */

#include "MustlStandard.h"

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore.h"
#endif
#endif

#endif
