//%includeGuardStart {
#ifndef GLSTL_H
#define GLSTL_H
//%includeGuardStart } lkGvxKI6nIS+LBBCIq/11A
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLSTL.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5QAMluTW550/qHVPreeEKA
/*
 * $Id: GLSTL.h,v 1.2 2003/08/21 23:08:28 southa Exp $
 * $Log: GLSTL.h,v $
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
#include "MushcoreSTL.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
