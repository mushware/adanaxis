//%includeGuardStart {
#ifndef MUSHPIESTANDARD_H
#define MUSHPIESTANDARD_H
//%includeGuardStart } eDZnA6C9x45TUj9pZaJNSQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieStandard.h
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
//%Header } YKTc2SSRbQQb+RbAF5upkA
/*
 * $Id: MushPieStandard.h,v 1.5 2005/05/19 13:02:13 southa Exp $
 * $Log: MushPieStandard.h,v $
 * Revision 1.5  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
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
#include "Mushcore/Mushcore.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#elif defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh/MushMesh.h"
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
