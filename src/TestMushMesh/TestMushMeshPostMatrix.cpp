//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPostMatrix.cpp
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
//%Header } d6NyqeKiyWNmFIJHBvrCIA
/*
 * $Id: TestMushMeshPostMatrix.cpp,v 1.3 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshPostMatrix.cpp,v $
 * Revision 1.3  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:23  southa
 * Mac release work
 *
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
