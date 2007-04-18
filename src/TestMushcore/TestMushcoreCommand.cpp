//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreCommand.cpp
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
//%Header } 4m/oU7tT1TstbwxmiHJdUw
/*
 * $Id: TestMushcoreCommand.cpp,v 1.8 2006/06/01 15:40:04 southa Exp $
 * $Log: TestMushcoreCommand.cpp,v $
 * Revision 1.8  2006/06/01 15:40:04  southa
 * DrawArray verification and fixes
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
 * Revision 1.2  2003/02/04 00:11:05  southa
 * Build fixes
 *
 * Revision 1.1  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 */

#include "TestMushcoreCommand.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushcoreCommandInstaller(TestMushcoreCommand::Install);

void
TestMushcoreCommand::ValueTest(const string& inName, const MushcoreScalar& inScalar)
{
    MushcoreScalar testValue = MushcoreGlobalConfig::Sgl().Get(inName);
    if (testValue != inScalar)
    {
        ostringstream message;
        message << "Variable test " << testValue << " != " << inScalar;
        throw MushcoreLogicFail(message.str());
    }
}

MushcoreScalar
TestMushcoreCommand::TestCommand(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    
    MushcoreFunction mushFunc;
    mushFunc.CommandAdd("configset('VAL1', -57)");
    mushFunc.CommandAdd("configset('VAL2', 45);");
    mushFunc.CommandAdd("configset('VALSUM', $VAL1+$VAL2)");
    mushFunc.CommandAdd("configset('VALDIFF', $VAL1-$VAL2)");
    mushFunc.CommandAdd("configset('EXPR1', $VAL1+35-12+$VAL2-7)");
    mushFunc.CommandAdd("configset('EXPR2', $VAL1+(35-(12+($VAL2-7))))");
    mushFunc.CommandAdd("configset('EXPR3', $VAL1+-$VAL2)");
    mushFunc.CommandAdd("configset('VAR_NAME', 'STRING1')");
    mushFunc.CommandAdd("configset($VAR_NAME, 'abc')");
    mushFunc.CommandAdd("configset('STRING2', 'fgh')");
    mushFunc.CommandAdd("configset('STRING3', $STRING1+$STRING2)");
    mushFunc.ThrowErrorExecute();

    tVal val1=-57;
    tVal val2=45;
    
    ValueTest("VALSUM", MushcoreScalar(val1+val2));
    ValueTest("VALDIFF", MushcoreScalar(val1-val2));
    ValueTest("EXPR1", MushcoreScalar(val1+35-12+val2-7));
    ValueTest("EXPR2", MushcoreScalar(val1+(35-(12+(val2-7)))));
    ValueTest("EXPR3", MushcoreScalar(val1+-val2));
    ValueTest("STRING3", MushcoreScalar("abcfgh"));

    return MushcoreScalar(0);
}

void
TestMushcoreCommand::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcorecommand", TestCommand);
}
