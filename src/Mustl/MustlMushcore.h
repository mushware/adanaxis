//%includeGuardStart {
#ifndef MUSTLMUSHCORE_H
#define MUSTLMUSHCORE_H
//%includeGuardStart } h+gqfDecxXjckM8W23Hqdg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcore.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 8/M1CFhIcI7Z3WyR+LdnLw
/*
 * $Id: MustlMushcore.h,v 1.6 2005/05/19 13:02:19 southa Exp $
 * $Log: MustlMushcore.h,v $
 * Revision 1.6  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:28  southa
 * Fixed file headers
 *
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
#include "Mushcore/Mushcore.h"
#endif
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
