/*
 * $Id: CoreCommand.cpp,v 1.1 2002/03/02 12:08:23 southa Exp $
 * $Log: CoreCommand.cpp,v $
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
    CoreInterpreter::Instance().Execute(m_string);
}
