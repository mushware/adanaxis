/*
 * $Id: CoreCommand.cpp,v 1.4 2002/03/05 22:44:45 southa Exp $
 * $Log: CoreCommand.cpp,v $
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

#include "CoreCommand.hp"
#include "CoreEnv.hp"
#include "CoreInterpreter.hp"
#include "CoreFlex.hp"

void
CoreCommand::Execute(void)
{
    CoreEnv env;
    Execute(env);
}

void
CoreCommand::Execute(CoreEnv& ioEnv)
{
    m_bison.Parse(*this);
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

Val
CoreCommand::PopVal(void)
{
    Val retVal;
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
