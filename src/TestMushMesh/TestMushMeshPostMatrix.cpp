//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPostMatrix.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } udmyXvNPsO21nx1KQbmGug
/*
 * $Id: TestMushMeshPostMatrix.cpp,v 1.1 2004/12/06 20:44:18 southa Exp $
 * $Log: TestMushMeshPostMatrix.cpp,v $
 * Revision 1.1  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
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
