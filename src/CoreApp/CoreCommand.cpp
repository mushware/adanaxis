/*
 * $Id$
 * $Log$
 */

#include "CoreCommand.hp"
#include "CoreEnv.hp"
#include "CoreInterpreter.hp"

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
