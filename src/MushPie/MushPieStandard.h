//%includeGuardStart {
#ifndef MUSHPIESTANDARD_H
#define MUSHPIESTANDARD_H
//%includeGuardStart } eDZnA6C9x45TUj9pZaJNSQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rYJRsdhM+/o+yEinlvmmIg
/*
 * $Id: MushPieStandard.h,v 1.2 2004/01/02 17:31:48 southa Exp $
 * $Log: MushPieStandard.h,v $
 * Revision 1.2  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#elif defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh.h"
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
