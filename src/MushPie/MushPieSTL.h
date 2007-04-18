//%includeGuardStart {
#ifndef MUSHPIESTL_H
#define MUSHPIESTL_H
//%includeGuardStart } s1VDDs8uoifg5yG0M4Ld0Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSTL.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } bnkfVyBPZNmISWXK/UxmLw
/*
 * $Id: MushPieSTL.h,v 1.6 2006/06/22 19:07:34 southa Exp $
 * $Log: MushPieSTL.h,v $
 * Revision 1.6  2006/06/22 19:07:34  southa
 * Build fixes
 *
 * Revision 1.5  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 * Revision 1.2  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
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
