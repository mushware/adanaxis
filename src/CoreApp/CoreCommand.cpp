/*
 * $Id: CoreCommand.cpp,v 1.8 2002/05/28 13:07:03 southa Exp $
 * $Log: CoreCommand.cpp,v $
 * Revision 1.8  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.7  2002/05/24 16:23:09  southa
 * Config and typenames
 *
 * Revision 1.6  2002/05/10 16:39:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.4  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.3  2002/03/04 22:30:48  southa
 * Interpreter work
 *
 * Revision 1.2  2002/03/02 20:35:07  southa
 * Added flex and bison parser
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreCommand.h"
#include "CoreEnv.h"
#include "CoreInterpreter.h"
#include "CoreFlex.h"
#include "CoreException.h"

void
CoreCommand::Execute(void)
{
    Execute(CoreEnv::Instance());
}

void
CoreCommand::Execute(CoreEnv& ioEnv)
{
    if (m_bison.Parse(*this))
    {
        throw(CommandFail("Syntax error in '" + m_string + "'"));
    }
}

string
CoreCommand::AllParams(void)
{
    string retStr;
    bool first=true;
    while (!m_paramList.Empty())
    {
        if (first)
        {
            first=false;
        }
        else
        {
            retStr.append(" ");
        }
        string str;
        m_paramList.PopParam(str);
        retStr.append(str);
    }
    return retStr;
}

string
CoreCommand::PopString(void)
{
    string retStr;
    m_paramList.PopParam(retStr);
    return retStr;
}

tVal
CoreCommand::PopVal(void)
{
    tVal retVal;
    m_paramList.PopParam(retVal);
    return retVal;
}

CoreScalar
CoreCommand::Despatch(void)
{
    cerr << "Command was " << Name() << "(";
    cerr << m_paramList << ")" << endl;
    return CoreInterpreter::Instance().Execute(*this);
}
