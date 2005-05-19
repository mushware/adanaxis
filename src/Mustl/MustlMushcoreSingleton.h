//%includeGuardStart {
#ifndef MUSTLMUSHCORESINGLETON_H
#define MUSTLMUSHCORESINGLETON_H
//%includeGuardStart } flYXKRCcGzn8LqLrF+jzMw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcoreSingleton.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0ghKUUGt6yRJlmYKOrKIZg
/*
 * $Id: MustlMushcoreSingleton.h,v 1.7 2004/09/26 21:07:15 southa Exp $
 * $Log: MustlMushcoreSingleton.h,v $
 * Revision 1.7  2004/09/26 21:07:15  southa
 * Mustl compilation fixes
 *
 * Revision 1.6  2004/01/02 21:13:15  southa
 * Source conditioning
 *
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
#include "Mushcore/MushcoreSingleton.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
