//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPreMatrix.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } UYsoSZkaMLApIrAjLIrskA
/*
 * $Id: TestMushMeshPreMatrix.cpp,v 1.1 2004/10/31 09:22:51 southa Exp $
 * $Log: TestMushMeshPreMatrix.cpp,v $
 * Revision 1.1  2004/10/31 09:22:51  southa
 * Added MushMeshPreMatrix
 *
 */

#include "TestMushMeshPreMatrix.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshPreMatrix(TestMushMeshPreMatrix::Install);

MushcoreScalar
TestMushMeshPreMatrix::TestPreMatrix(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    for (U32 i=0; i<4; ++i)
    {
        for (U32 j=0; j<4; ++j)
        {
            
            MushMeshPreMatrix<tVal, 4, 4> preMatrix
            (
                MushMeshVector<tVal, 4>(0, 0, 0, 0),
                MushMeshVector<tVal, 4>(0, 0, 0, 0),
                MushMeshVector<tVal, 4>(0, 0, 0, 0),
                MushMeshVector<tVal, 4>(0, 0, 0, 0)
            );
            
            preMatrix.RCSet(2, i, j);
            
            MushMeshVector<tVal, 4> postVector(3, 5, 7, 11);
            MushMeshVector<tVal, 4> resultVector(0, 0, 0, 0);
    
            resultVector.Set(2*postVector[j], i);
            
            if (preMatrix * postVector != resultVector)
            {
                ostringstream message;
                message << "operator Matrix*vector failed : " << preMatrix << " * " << postVector << " != " << preMatrix * postVector;
                throw(MushcoreLogicFail(message.str()));
            }
        }
    }
    return MushcoreScalar(0);
}

void
TestMushMeshPreMatrix::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshprematrix", TestPreMatrix);
}
