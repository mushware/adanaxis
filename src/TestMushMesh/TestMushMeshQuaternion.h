//%includeGuardStart {
#ifndef TESTMUSHMESHQUATERNION_H
#define TESTMUSHMESHQUATERNION_H
//%includeGuardStart } QsO6VqLi2p68/1q8tHLJKQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshQuaternion.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } IGm5hs1NDR/Kfi2ovqwa2g
/*
 * $Id: TestMushMeshQuaternion.h,v 1.2 2004/12/12 10:55:37 southa Exp $
 * $Log: TestMushMeshQuaternion.h,v $
 * Revision 1.2  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.1  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshQuaternion
{
public:
    static void PseudoRandomRotationGet(Mushware::t4x4Val& outMatrix, Mushware::tVal inSeed);
    static void PseudoRandomVectorGet(Mushware::t4Val& outVector, Mushware::tVal inSeed);
    static MushcoreScalar TestQuaternion(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
