//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshBox.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } aN1UZCrWmgRxSG4S3+dPvQ
/*
 * $Id$
 * $Log$
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

    testBox.RegularMake();

    if (testBox != tTestBox(2,5,4,8))
    {
        ostringstream message;
        message << "RegularMake failed: " << testBox << " != " << tTestBox(2,5,4,8);
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

    if (testBox.SizeGet() != tPoint(3, 2))
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
    MushcoreInterpreter::Sgl().HandlerAdd("testbox", TestBox);
}
