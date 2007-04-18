//%includeGuardStart {
#ifndef MUSHRENDERSTANDARD_H
#define MUSHRENDERSTANDARD_H
//%includeGuardStart } t0B9YwsGnsVt9W31vpaEEg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderStandard.h
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
//%Header } USjfSHKTjdbTKyHpN0jpbg
/*
 * $Id: MushRenderStandard.h,v 1.3 2006/06/22 19:07:35 southa Exp $
 * $Log: MushRenderStandard.h,v $
 * Revision 1.3  2006/06/22 19:07:35  southa
 * Build fixes
 *
 * Revision 1.2  2006/06/01 15:39:39  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/01 10:36:46  southa
 * MushRender work
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
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
