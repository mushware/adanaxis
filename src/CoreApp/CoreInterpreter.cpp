/*
 * $Id: CoreInterpreter.cpp,v 1.2 2002/03/05 22:44:46 southa Exp $
 * $Log: CoreInterpreter.cpp,v $
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreInterpreter.hp"
#include "CoreCommandHandler.hp"
#include "CoreException.hp"

CoreInterpreter *CoreInterpreter::m_instance = NULL;

CoreScalar
CoreInterpreter::Execute(CoreCommand& ioCommand)
{
    CoreEnv ioEnv;
    CoreScalar retScalar(0);
    if (m_handlers.find(ioCommand.Name()) != m_handlers.end())
    {
        try
        {
            retScalar=m_handlers[ioCommand.Name()](ioCommand, ioEnv);
        }
        catch (FileFail& f)
        {
            cerr << "File operation failed: " << f << endl;
        }
    }
    else
    {
        cerr << "Unknown command '" << ioCommand.Name() << "'" << endl;
    }
    return retScalar;
}

void
CoreInterpreter::AddHandler(const string& inName, CoreCommandHandler inHandler)
{
    m_handlers[inName]=inHandler;
}
