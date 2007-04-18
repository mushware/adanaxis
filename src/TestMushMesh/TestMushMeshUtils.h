//%includeGuardStart {
#ifndef TESTMUSHMESHUTILS_H
#define TESTMUSHMESHUTILS_H
//%includeGuardStart } QJ2iZCD/JA8PFM6LBdWsHw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshUtils.h
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
//%Header } htLpV+3+dibxMowGaRCo6w
/*
 * $Id: TestMushMeshUtils.h,v 1.4 2006/05/01 17:39:01 southa Exp $
 * $Log: TestMushMeshUtils.h,v $
 * Revision 1.4  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshUtils
{
public:
    static bool ApproxEquals(Mushware::t4Val inVec1, Mushware::t4Val inVec2);
    static MushcoreScalar TestUtils(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
