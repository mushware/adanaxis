//%includeGuardStart {
#ifndef MUSHMESHSTANDARD_H
#define MUSHMESHSTANDARD_H
//%includeGuardStart } fMBJTUeUxG+dP9rT1wCfxg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 7tVHoBg9eeZiZvmzxRxBhw

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreStandard.h>
#include <Mushcore/MushcoreIO.h>
#include <Mushcore/MushcoreFail.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreStandard.h>
#include <MushcoreIO.h>
#include <MushcoreFail.h>
#else
#include "MushcoreStandard.h"
#include "MushcoreIO.h"
#include "MushcoreFail.h"
#endif
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
