//%includeGuardStart {
#ifndef MUSHMUSTL_H
#define MUSHMUSTL_H
//%includeGuardStart } KBVRriTEzxvrJPJCRBYpXg
//%Header {
/*****************************************************************************
 *
 * File: src/API/mushMustl.h
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
//%Header } or6F5iMCqPlHc0eR188xYQ
/*
 * $Id: mushMustl.h,v 1.2 2005/05/19 13:01:57 southa Exp $
 * $Log: mushMustl.h,v $
 * Revision 1.2  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/06 20:46:49  southa
 * Build fixes
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSTL_MUSTL_H)
#include <Mustl/Mustl.h>
#elif defined(HAVE_MUSTL_H)
#include <Mustl.h>
#else
#include "Mustl/Mustl.h"
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
