//%includeGuardStart {
#ifndef MUSTLMUSHCORESINGLETON_H
#define MUSTLMUSHCORESINGLETON_H
//%includeGuardStart } flYXKRCcGzn8LqLrF+jzMw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcoreSingleton.h
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rQYYs6H5wr6GWkvXSe4Ezw
/*
 * $Id: MustlMushcoreSingleton.h,v 1.5 2003/09/17 19:40:38 southa Exp $
 * $Log: MustlMushcoreSingleton.h,v $
 * Revision 1.5  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:28  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/02/05 17:36:36  southa
 * Build fixes
 *
 * Revision 1.2  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.1  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
 */

#include "MustlStandard.h"


#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSingleton.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreSingleton.h>
#else
#include "MushcoreSingleton.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
