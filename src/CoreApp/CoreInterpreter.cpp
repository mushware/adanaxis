/*
 * $Id: CoreInterpreter.cpp,v 1.1 2002/03/02 12:08:23 southa Exp $
 * $Log: CoreInterpreter.cpp,v $
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreInterpreter.hp"
#include "CoreCommandHandler.hp"

CoreInterpreter *CoreInterpreter::m_instance = NULL;

CoreScalar
CoreInterpreter::Execute(CoreCommand& ioCommand)
{
    CoreEnv ioEnv;
    CoreScalar retScalar(0);
    if (m_handlers.find(ioCommand.Name()) != m_handlers.end())
    {
        retScalar=m_handlers[ioCommand.Name()]->Execute(ioCommand, ioEnv);
    }
    else
    {
        cerr << "Unknown command '" << ioCommand.Name() << "'" << endl;
    }
    return retScalar;
}

void
CoreInterpreter::AddHandler(const string& inName, CoreCommandHandler& inHandler)
{
    m_handlers[inName]=&inHandler;
}
