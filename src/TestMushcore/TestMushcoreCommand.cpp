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
 * $Id: TestMushcoreCommand.cpp,v 1.1 2003/01/20 17:03:22 southa Exp $
 * $Log: TestMushcoreCommand.cpp,v $
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
    MushcoreInterpreter::Sgl().HandlerAdd("testcommand", TestCommand);
}
