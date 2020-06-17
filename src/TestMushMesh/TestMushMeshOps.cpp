//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshOps.cpp
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
//%Header } D9tPOgYhnWffi2W4vPNPzw
/*
 * $Id: TestMushMeshOps.cpp,v 1.4 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshOps.cpp,v $
 * Revision 1.4  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.2  2004/11/30 00:18:06  southa
 * Additional vector operations
 *
 * Revision 1.1  2004/11/17 23:43:48  southa
 * Added outer product
 *
 */

#include "TestMushMeshOps.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshOps(TestMushMeshOps::Install);

MushcoreScalar
TestMushMeshOps::TestInnerProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    t4Val aVec(4, 3, 2, 1);
    t4Val bVec(1, 1, -3, -1);

    if (aVec * aVec != 30)
    {
        ostringstream message;
        message << "InnerProduct failed : " << aVec << " * " << bVec;
        message << " = " << aVec * aVec << " (expected 30)";
        throw(MushcoreLogicFail(message.str()));
    }

    if (aVec * aVec != 30)
    {
        ostringstream message;
        message << "InnerProduct failed : " << aVec << " * " << aVec;
        message << " = " << aVec * aVec << " (expected 30)";
        throw(MushcoreLogicFail(message.str()));
    }
    
    if (aVec * bVec != 0)
    {
        ostringstream message;
        message << "InnerProduct failed : " << aVec << " * " << bVec;
        message << " = " << aVec * bVec << " (expected 0)";
        throw(MushcoreLogicFail(message.str()));
    }
    
    
    return MushcoreScalar(0);
}    

MushcoreScalar
TestMushMeshOps::TestOuterProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    t4Val aVec(1, 0, 0, 0);
    t4Val bVec(0, 1, 0, 0);
    t4Val cVec(0, 0, 1, 0);
    t4Val dVec(0, 0, 0, 1);

    t4Val resultVec;
    
    resultVec = MushMeshOps::OuterProduct(aVec, bVec, cVec);
    
    if (resultVec != dVec)
    {
        ostringstream message;
        message << "OuterProduct failed : " << aVec << " ^ " << bVec << " ^ " << cVec;
        message << " = " << resultVec << " (expected " << dVec << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    for (tVal i=0; i<100; ++i)
    {
        // Verify the orthogonality condition for each vector
        aVec = t4Val(sin(1+i), cos(2+i), sin(3+i), cos(4+i));
        bVec = t4Val(cos(5+i), cos(6+i), sin(7+i), cos(8+i));
        cVec = t4Val(sin(9+i), cos(10+i), cos(11+i), cos(12+i));
        
        tVal limit = 1e-6;
        
        resultVec = MushMeshOps::OuterProduct(aVec, bVec, cVec);
        
        if (resultVec * aVec > limit)
        {
            ostringstream message;
            message << "OuterProduct not orthgonal to A : " << aVec << " ^ " << bVec << " ^ " << cVec;
            message << " = " << resultVec << ", dot = " << resultVec * aVec;
            throw(MushcoreLogicFail(message.str()));
        }
        if (resultVec * bVec > limit)
        {
            ostringstream message;
            message << "OuterProduct not orthgonal to A : " << aVec << " ^ " << bVec << " ^ " << cVec;
            message << " = " << resultVec << ", dot = " << resultVec * bVec;
            throw(MushcoreLogicFail(message.str()));
        }
        if (resultVec * cVec > limit)
        {
            ostringstream message;
            message << "OuterProduct not orthgonal to A : " << aVec << " ^ " << bVec << " ^ " << cVec;
            message << " = " << resultVec << ", dot = " << resultVec * cVec;
            throw(MushcoreLogicFail(message.str()));
        }
    }    
        
    return MushcoreScalar(0);
}

MushcoreScalar
TestMushMeshOps::TestNormalise(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    t4Val aVec(7, 5, 3, 1);
    tVal length = std::sqrt(7*7+5*5+3*3+1.0);
    t4Val resultVec(7/length, 5/length, 3/length, 1/length);
    
    MushMeshOps::Normalise(aVec);
    
    if (resultVec != aVec)
    {
        ostringstream message;
        message << "Normalise failed : Normalise(" << aVec << ") != " << resultVec;
        throw(MushcoreLogicFail(message.str()));
    }
    
    if (std::fabs(1.0 - resultVec * resultVec) > 1e-6)
    {
        ostringstream message;
        message << "Normalise failed : Normalise(" << aVec << ") not unit length";
        throw(MushcoreLogicFail(message.str()));
    }
    
    return MushcoreScalar(0);
}    

MushcoreScalar
TestMushMeshOps::TestSlerp(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    t4Val aVec(1, 0, 0, 0);
    t4Val bVec(0, 1, 0, 0);
    t4Val expectedVec(std::sqrt(2.0)/2, std::sqrt(2.0)/2, 0, 0);
    
    t4Val resultVec = MushMeshOps::SlerpNormalised(aVec, bVec, 0.5);
    
    if (!MushMeshOps::ApproxEquals(resultVec, expectedVec))
    {
        ostringstream message;
        message << "Normalise failed : Slerp(" << aVec << ", " <<bVec << ", 0.5) = " << resultVec;
        message << " (expected " << expectedVec << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    resultVec = MushMeshOps::SlerpNormalised(aVec, bVec, 0.25);
    resultVec = MushMeshOps::SlerpNormalised(resultVec, bVec, 1.0/3);
    if (!MushMeshOps::ApproxEquals(resultVec, expectedVec))
    {
        ostringstream message;
        message << "Normalise failed : Double Slerp = " << resultVec;
        message << " (expected " << expectedVec << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    bVec = t4Val(-1, 1e-5, 0, 0);

    expectedVec = t4Val(0, 1, 0, 0);
    resultVec = MushMeshOps::SlerpNormalised(aVec, bVec, 0.5);
    
    if (!MushMeshOps::ApproxEquals(resultVec, expectedVec))
    {
        ostringstream message;
        message << "Normalise failed : Slerp(" << aVec << ", " <<bVec << ", 0.5) = " << resultVec;
        message << " (expected " << expectedVec << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    bVec = t4Val(-1, 0, 0, 0);
    
    expectedVec = t4Val(0, 1, 0, 0);
    resultVec = MushMeshOps::SlerpNormalised(aVec, bVec, 0.5);
    
    if (!MushMeshOps::ApproxEquals(resultVec, expectedVec))
    {
        ostringstream message;
        message << "Normalise failed : Slerp(" << aVec << ", " <<bVec << ", 0.5) = " << resultVec;
        message << " (expected " << expectedVec << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    resultVec = MushMeshOps::SlerpNormalised(aVec, aVec, 0.5);
    
    if (!MushMeshOps::ApproxEquals(resultVec, aVec))
    {
        ostringstream message;
        message << "Normalise failed : Slerp(" << aVec << ", " << aVec << ", 0.5) = " << resultVec;
        message << " (expected " << expectedVec << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    return MushcoreScalar(0);
}

void
TestMushMeshOps::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshinnerproduct", TestInnerProduct);
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshouterproduct", TestOuterProduct);
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshnormalise", TestNormalise);
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshslerp", TestSlerp);
}
