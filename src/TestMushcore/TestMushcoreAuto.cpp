/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: TestMushcoreAuto.cpp,v 1.1 2003/01/20 15:38:28 southa Exp $
 * $Log: TestMushcoreAuto.cpp,v $
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 */

#include "TestMushcoreAuto.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushcoreAutoInstaller(TestMushcoreAuto::Install);

MushcoreScalar
TestMushcoreAuto::TestAuto(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    char workspace[]="hello";

    MushcoreAutoMonkey& monkey1=*new MushcoreAutoMonkey;
    if (monkey1.ReferenceCountGet() != 1)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 1");
    }

    if (!monkey1.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 2");
    }
    MushcoreAutoMonkey& monkey2=*new MushcoreAutoMonkey(monkey1);
    if (monkey1.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 3");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 4");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 5");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 6");
    }
    monkey1=monkey1;
    if (monkey1.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 7");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 8");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 9");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 10");
    }
    monkey1=monkey2;
    if (monkey1.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 11");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 12");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 13");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 14");
    }
    MushcoreAutoMonkey& monkey3=*new MushcoreAutoMonkey;
    MushcoreAutoMonkey& monkey4=*new MushcoreAutoMonkey(monkey3);
    if (monkey3.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 40");
    }
    if (monkey4.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 41");
    }
    if (monkey3.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 42");
    }
    if (monkey4.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 43");
    }
    monkey3=monkey2;
    if (monkey4.ReferenceCountGet() != 1)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 44");
    }
    if (!monkey4.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 45");
    }
    if (monkey3.ReferenceCountGet() != 3)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 46");
    }
    if (monkey2.ReferenceCountGet() != 3)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 47");
    }
    if (monkey1.ReferenceCountGet() != 3)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 48");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 49");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 50");
    }
    if (monkey3.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 51");
    }
    delete &monkey1;
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 80");
    }
    if (monkey3.ReferenceCountGet() != 2)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 81");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 82");
    }
    if (monkey3.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 83");
    }
    delete &monkey2;
    if (monkey3.ReferenceCountGet() != 1)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 84");
    }
    if (!monkey3.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 85");
    }
    delete &monkey3;
    if (monkey4.ReferenceCountGet() != 1)
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 86");
    }
    if (!monkey4.FreeInDestructor(workspace))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 87");
    }
    delete &monkey4;
    // All monkeys gone
    MushcoreAutoMonkey& monkey5=*new MushcoreAutoMonkey;

    if (monkey5.FreeInDestructor(NULL))
    {
        throw MushcoreLogicFail("MushcoreAutoMonkey fault 100");
    }
    delete &monkey5;
    return MushcoreScalar(0);
}

void
TestMushcoreAuto::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testauto", TestAuto);
}

