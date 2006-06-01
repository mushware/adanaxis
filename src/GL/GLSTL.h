//%includeGuardStart {
#ifndef GLSTL_H
#define GLSTL_H
//%includeGuardStart } lkGvxKI6nIS+LBBCIq/11A
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLSTL.h
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
//%Header } EsekgUEeuyc667Geeh0gpw
/*
 * $Id: GLSTL.h,v 1.6 2005/05/19 13:02:00 southa Exp $
 * $Log: GLSTL.h,v $
 * Revision 1.6  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:08:28  southa
 * Fixed file headers
 *
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
#include "Mushcore/MushcoreSTL.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
