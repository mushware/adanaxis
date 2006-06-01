//%includeGuardStart {
#ifndef MUSHGAMESTANDARD_H
#define MUSHGAMESTANDARD_H
//%includeGuardStart } PZ6kre97A1TFf2hJNDPD+Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameStandard.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } o+BSM01bjQYGzqTGFYVwpg
/*
 * $Id: MushGameStandard.h,v 1.4 2005/07/27 18:07:25 southa Exp $
 * $Log: MushGameStandard.h,v $
 * Revision 1.4  2005/07/27 18:07:25  southa
 * Collision checking
 *
 * Revision 1.3  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.2  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.1  2005/06/14 13:25:34  southa
 * Adanaxis work
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

namespace Mushware
{
    typedef Mushware::U64 tGameUsec;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
