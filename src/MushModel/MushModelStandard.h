//%includeGuardStart {
#ifndef MUSHMODELSTANDARD_H
#define MUSHMODELSTANDARD_H
//%includeGuardStart } JegAGJHGOh2Qcfuu3rwbSA
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelStandard.h
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
//%Header } 08jWxw5L1aUw7u2rp84eNw
/*
 * $Id: MushModelStandard.h,v 1.4 2006/06/22 19:07:34 southa Exp $
 * $Log: MushModelStandard.h,v $
 * Revision 1.4  2006/06/22 19:07:34  southa
 * Build fixes
 *
 * Revision 1.3  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
