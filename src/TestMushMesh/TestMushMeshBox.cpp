//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshBox.cpp
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
//%Header } iKum3f99Gn46cn8ojcNK+Q
/*
 * $Id: TestMushMeshBox.cpp,v 1.4 2004/01/05 20:13:15 southa Exp $
 * $Log: TestMushMeshBox.cpp,v $
 * Revision 1.4  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/17 19:33:11  southa
 * Mesh patches
 *
 * Revision 1.1  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 */

#include "TestMushMeshBox.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshBoxInstaller(TestMushMeshBox::Install);

MushcoreScalar
TestMushMeshBox::TestBox(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    typedef MushMeshBox<U32> tTestBox;
    typedef t2U32 tPoint;

    tTestBox testBox(4,5,2,8);

    if (testBox.RegularIs())
    {
        ostringstream message;
        message << "RegularIs failed: " << testBox << " not regular";
        throw(MushcoreLogicFail(message.str()));
    }

    testBox.RegularMake();

    if (testBox != tTestBox(2,5,4,8))
    {
        ostringstream message;
        message << "RegularMake failed: " << testBox << " != " << tTestBox(2,5,4,8);
        throw(MushcoreLogicFail(message.str()));
    }

    if (!testBox.RegularIs())
    {
        ostringstream message;
        message << "RegularIs failed: " << testBox << " is regular";
        throw(MushcoreLogicFail(message.str()));
    }

    testBox = tTestBox(4,3,2,1);
    testBox.RegularMake();

    if (testBox != tTestBox(2,1,4,3))
    {
        ostringstream message;
        message << "RegularMake failed: " << testBox << " != " << tTestBox(2,1,4,3);
        throw(MushcoreLogicFail(message.str()));
    }

    testBox.StartSet(tPoint(testBox.StartGet().Y(), testBox.StartGet().X()));
    if (testBox != tTestBox(1,2,4,3))
    {
        ostringstream message;
        message << "StartSet/Get failed: " << testBox << " != " << tTestBox(1,2,4,3);
        throw(MushcoreLogicFail(message.str()));
    }

    if (testBox.SizeGet() != tPoint(3, 1))
    {
        ostringstream message;
        message << "SizeGet failed: " << testBox.SizeGet() << " != " << tPoint(3, 1);
        throw(MushcoreLogicFail(message.str()));
    }
    

    testBox.EndSet(tPoint(testBox.EndGet().Y(), testBox.EndGet().X()));
    if (testBox != tTestBox(1,2,3,4))
    {
        ostringstream message;
        message << "EndSet/Get failed: " << testBox << " != " << tTestBox(1,2,3,4);
        throw(MushcoreLogicFail(message.str()));
    }

    return MushcoreScalar(0);
}

void
TestMushMeshBox::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshbox", TestBox);
}
