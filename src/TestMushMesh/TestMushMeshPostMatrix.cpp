//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPostMatrix.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } eTU8AuzqLFeEhRMkyWZmxg
/*
 * $Id$
 * $Log$
 */

#include "TestMushMeshPostMatrix.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshPostMatrix(TestMushMeshPostMatrix::Install);

MushcoreScalar
TestMushMeshPostMatrix::TestPostMatrix(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    t4x4Val aMatrix, bMatrix, resultMatrix, expectedMatrix;
    
    for (U32 r=0; r<4; ++r)
    {
        for (U32 c=0; c<4; ++c)
        {
            aMatrix.RCSet((r+1)*(c+3), r, c);
            bMatrix.RCSet((r+5)*(c+7), r, c);
        }
    }
    
    for (U32 r=0; r<4; ++r)
    {
        for (U32 c=0; c<4; ++c)
        {
            tVal result = 0;
            for (U32 i=0; i<4; ++i)
            {
                result += aMatrix.RCGet(r, i) * bMatrix.RCGet(i, c);
            }
            expectedMatrix.RCSet(result, r, c);
        }
    }
    
    resultMatrix = aMatrix * bMatrix;
    
    if (resultMatrix != expectedMatrix)
    {
        ostringstream message;
        message << "operator Matrix*Matrix failed : " << aMatrix << " * " << bMatrix << " != " << resultMatrix << " (expected " << expectedMatrix << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    return MushcoreScalar(0);
}

void
TestMushMeshPostMatrix::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshpostmatrix", TestPostMatrix);
}
