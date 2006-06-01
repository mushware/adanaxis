//%includeGuardStart {
#ifndef PLATFORMSTL_H
#define PLATFORMSTL_H
//%includeGuardStart } c6BJvuqH/nmO1Ri2q+FOMg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformSTL.h
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
//%Header } YgY2xz10I/tOK3mTABcO7A
/*
 * $Id: PlatformSTL.h,v 1.6 2005/05/19 13:02:21 southa Exp $
 * $Log: PlatformSTL.h,v $
 * Revision 1.6  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:34  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 14:32:03  southa
 * Build frameworks for Mac OS X
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSTL.h>
#elif defined(HAVE_MUSHCORE_H)
#include <MushcoreSTL.h>
#else
#include "Mushcore/MushcoreSTL.h"
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
