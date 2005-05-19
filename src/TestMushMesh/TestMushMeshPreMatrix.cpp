//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPreMatrix.cpp
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
//%Header } WXSUqUaawtXDzHNskFcJuQ
/*
 * $Id: TestMushMeshPreMatrix.cpp,v 1.2 2004/12/13 11:09:11 southa Exp $
 * $Log: TestMushMeshPreMatrix.cpp,v $
 * Revision 1.2  2004/12/13 11:09:11  southa
 * Quaternion and vector tweaks
 *
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
