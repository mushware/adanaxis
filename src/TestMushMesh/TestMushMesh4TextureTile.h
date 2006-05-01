//%includeGuardStart {
#ifndef TESTMUSHMESH4TEXTURETILE_H
#define TESTMUSHMESH4TEXTURETILE_H
//%includeGuardStart } XeFFQ3aZ3yQxRY9GTyZ4CQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4TextureTile.h
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
//%Header } oCfNDL0ixZ21gseEO8MqsA
/*
 * $Id$
 * $Log$
 */

#include "TestMushMeshStandard.h"

class TestMushMesh4TextureTile
{
public:
    static void TransformTest(const MushMesh4TextureTile& inTile,
                              const Mushware::t2Val& inTestVec,
                              const Mushware::t4Val& inExpectedVec);
    static MushcoreScalar Test4TextureTile(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
