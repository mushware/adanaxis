//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshMattress.cpp
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
//%Header } zW6Rr3FQYHsr9rFEgeLtzQ
/*
 * $Id: TestMushMeshMattress.cpp,v 1.3 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshMattress.cpp,v $
 * Revision 1.3  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.1  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 */

#include "TestMushMeshMattress.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshMattress(TestMushMeshMattress::Install);

MushcoreScalar
TestMushMeshMattress::TestMattress(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreXMLOStream xmlOut(std::cout);
    
    t4Val testVec(1,2,3,4);
    t4x4Val testMatrix(t4Val(0,1,0,0),
                       t4Val(0,0,1,0),
                       t4Val(0,0,0,1),
                       t4Val(1,0,0,0));
    
    t4Val offsetVec(t4Val(2,3,4,5));
    t4x4o4Val testMattress(testMatrix, offsetVec);
    
    if (testMattress * (testMattress * testVec) != (testMattress * testMattress) * testVec)
    {
        throw MushcoreLogicFail("Mattress failure 1");
    }
    
#if 0
    xmlOut << testMattress;
    xmlOut << (testMattress * testVec);
    xmlOut << (testMattress * testMattress);
    xmlOut << testMattress * (testMattress * testVec);
    xmlOut << (testMattress * testMattress) * testVec;
#endif
    
    return MushcoreScalar(0);
}

void
TestMushMeshMattress::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshmattress", TestMattress);
}
