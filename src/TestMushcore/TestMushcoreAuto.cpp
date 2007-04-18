//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreAuto.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } ikJhDLww7CmtzM6uyCdPng
/*
 * $Id: TestMushcoreAuto.cpp,v 1.9 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushcoreAuto.cpp,v $
 * Revision 1.9  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 * Revision 1.7  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.5  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:37  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 */

#include "TestMushcoreAuto.h"

#include "TestMushcoreVirtualPointerObject.h"

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
    
    MushcoreAutoClonePtr<TestMushcoreVirtualPointerObject> clonePtr1(new TestMushcoreVirtualPointerObject);
    MushcoreAutoClonePtr<TestMushcoreVirtualPointerObject> clonePtr2(clonePtr1);
    
    clonePtr1->TestValueSet(3);
    clonePtr2->TestValueSet(4);
    if (clonePtr1->TestValue() != 3 || clonePtr2->TestValue() != 4)
    {
        throw MushcoreLogicFail("MushcoreAutoClonePtr fault 1");
    }
    
    
    return MushcoreScalar(0);
}

void
TestMushcoreAuto::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcoreauto", TestAuto);
}

