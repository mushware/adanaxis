//%includeGuardStart {
#ifndef INFERNALSTL_H
#define INFERNALSTL_H
//%includeGuardStart } TixJaqXfAoLocRM9KDH+vA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalSTL.h
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
//%Header } dQnO+Xy1cjqZkxHSUNI95Q
/*
 * $Id: InfernalSTL.h,v 1.6 2006/06/22 19:07:29 southa Exp $
 * $Log: InfernalSTL.h,v $
 * Revision 1.6  2006/06/22 19:07:29  southa
 * Build fixes
 *
 * Revision 1.5  2006/06/01 15:39:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.3  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:08:54  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/02/05 17:36:36  southa
 * Build fixes
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
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
