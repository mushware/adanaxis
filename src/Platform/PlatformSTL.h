//%includeGuardStart {
#ifndef PLATFORMSTL_H
#define PLATFORMSTL_H
//%includeGuardStart } c6BJvuqH/nmO1Ri2q+FOMg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformSTL.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wjQZt84EYLr8oY3hCh7fgg
/*
 * $Id: PlatformSTL.h,v 1.3 2003/09/17 19:40:38 southa Exp $
 * $Log: PlatformSTL.h,v $
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

#if defined(HAVE_MUSHCORE_MUSHCORESTL_H)
#include <Mushcore/MushcoreSTL.h>
#else
#if defined(HAVE_MUSHCORESTL_H)
#include <MushcoreSTL.h>
#else
#include "MushcoreSTL.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
