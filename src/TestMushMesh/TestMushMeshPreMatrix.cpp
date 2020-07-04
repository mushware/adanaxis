//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPreMatrix.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } SjkqXWk4RtcxeFVN7fqTIw
/*
 * $Id: TestMushMeshPreMatrix.cpp,v 1.4 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshPreMatrix.cpp,v $
 * Revision 1.4  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
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
