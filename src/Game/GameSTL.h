//%includeGuardStart {
#ifndef GAMESTL_H
#define GAMESTL_H
//%includeGuardStart } G7dt6ZU+Ufw7R53TpCyQmA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSTL.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } y0xiGDO93d4zR1w4Opnw9A
/*
 * $Id: GameSTL.h,v 1.3 2003/09/17 19:40:33 southa Exp $
 * $Log: GameSTL.h,v $
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSTL.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreSTL.h>
#else
#include "MushcoreSTL.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
