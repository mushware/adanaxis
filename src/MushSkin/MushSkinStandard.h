//%includeGuardStart {
#ifndef MUSHSKINSTANDARD_H
#define MUSHSKINSTANDARD_H
//%includeGuardStart } 0JxWq3a6V+Dso41CAvhe3A
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinStandard.h
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Ol4sGg34tVBOIxxSoDTglQ
/*
 * $Id: MushSkinStandard.h,v 1.1 2005/08/29 18:40:57 southa Exp $
 * $Log: MushSkinStandard.h,v $
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
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
#include "Mushcore/Mushcore.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#elif defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh/MushMesh.h"
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
