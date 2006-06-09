//%includeGuardStart {
#ifndef TESTMUSHMESHTOOLS_H
#define TESTMUSHMESHTOOLS_H
//%includeGuardStart } Ev4y5T3GaryJ7MTZGbMJQg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTools.h
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
//%Header } I//vP+u23kIqhtgoUF+l4Q
/*
 * $Id: TestMushMeshTools.h,v 1.1 2006/06/08 20:17:32 southa Exp $
 * $Log: TestMushMeshTools.h,v $
 * Revision 1.1  2006/06/08 20:17:32  southa
 * Texture tile generation method 2
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshTools
{
public:
    static bool ApproxEquals(Mushware::t4Val inVec1, Mushware::t4Val inVec2);
	static void TestFacetTransform(void);
    static MushcoreScalar TestTools(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
