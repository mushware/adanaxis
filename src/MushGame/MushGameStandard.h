//%includeGuardStart {
#ifndef MUSHGAMESTANDARD_H
#define MUSHGAMESTANDARD_H
//%includeGuardStart } PZ6kre97A1TFf2hJNDPD+Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameStandard.h
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
//%Header } VNAuBPSg3ag/sLGo+XjwKQ
/*
 * $Id: MushGameStandard.h,v 1.7 2006/10/09 16:00:17 southa Exp $
 * $Log: MushGameStandard.h,v $
 * Revision 1.7  2006/10/09 16:00:17  southa
 * Intern generation
 *
 * Revision 1.6  2006/06/22 19:07:32  southa
 * Build fixes
 *
 * Revision 1.5  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
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

#if defined(HAVE_MUSHRUBY_MUSHRUBY_H)
#include <MushRuby/MushRuby.h>
#elif defined(HAVE_MUSHRUBY_H)
#include <MushRuby.h>
#else
#include "MushRuby/MushRuby.h"
#endif

namespace Mushware
{
    typedef Mushware::U64 tGameUsec;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
