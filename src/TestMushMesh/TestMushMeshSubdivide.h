//%includeGuardStart {
#ifndef TESTMUSHMESHSUBDIVIDE_H
#define TESTMUSHMESHSUBDIVIDE_H
//%includeGuardStart } BgqjDqOHt2g1f9pgpwVQpA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshSubdivide.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cpsh/PUv+N7hZwaE5of9Kg
/*
 * $Id: TestMushMeshSubdivide.h,v 1.1 2003/10/15 11:54:55 southa Exp $
 * $Log: TestMushMeshSubdivide.h,v $
 * Revision 1.1  2003/10/15 11:54:55  southa
 * MushMeshArray neighbour testing and subdivision
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshSubdivide
{
public:
    static MushcoreScalar TestSubdivide(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
private:
    static void ArrayPrint(const MushMeshArray<Mushware::tVal>& inArray);
    static bool VerifySingle1(const MushMeshArray<Mushware::tVal>& inArray, const Mushware::t2U32& inCentre, Mushware::tVal inProp);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
