//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshOps.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0wIEHnMxizldt3KbK6uiaQ
/*
 * $Id: TestMushMeshOps.cpp,v 1.1 2004/10/31 09:22:51 southa Exp $
 * $Log: TestMushMeshOps.cpp,v $
 */

#include "TestMushMeshOps.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshOps(TestMushMeshOps::Install);

MushcoreScalar
TestMushMeshOps::TestOps(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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

void
TestMushMeshOps::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshops", TestOps);
}
