//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshMattress.cpp
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
//%Header } /3rWQ+PBevPGAR8k/1jYTA
/*
 * $Id: TestMushMeshMattress.cpp,v 1.1 2005/07/02 00:42:39 southa Exp $
 * $Log: TestMushMeshMattress.cpp,v $
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
