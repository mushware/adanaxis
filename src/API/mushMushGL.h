//%includeGuardStart {
#ifndef MUSHMUSHGL_H
#define MUSHMUSHGL_H
//%includeGuardStart } 73409qbWKt4XwsEIBqVdyg
//%Header {
/*****************************************************************************
 *
 * File: src/API/mushMushGL.h
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
//%Header } WQSc9hht9Rc3HhYm8yBWYQ
/*
 * $Id: mushMushGL.h,v 1.5 2006/06/22 19:07:26 southa Exp $
 * $Log: mushMushGL.h,v $
 * Revision 1.5  2006/06/22 19:07:26  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/01 15:38:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/07 12:06:22  southa
 * Rendering work
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHGL_MUSHGL_H)
#include <MushGL/MushGL.h>
#elif defined(HAVE_MUSHGL_H)
#include <MushGL.h>
#else
#include "MushGL/MushGL.h"
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
