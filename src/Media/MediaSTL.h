//%includeGuardStart {
#ifndef MEDIASTL_H
#define MEDIASTL_H
//%includeGuardStart } 49s9eOqW2RTUoIsat9M5Ew
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSTL.h
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
//%Header } L1ClAj5w8rlyPPja0Y2Ojg
/*
 * $Id: MediaSTL.h,v 1.7 2006/06/01 15:39:14 southa Exp $
 * $Log: MediaSTL.h,v $
 * Revision 1.7  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 15:01:19  southa
 * Fix Mustl command line build
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
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
