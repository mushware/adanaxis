/*
 * $Id: CoreInterpreter.cpp,v 1.4 2002/05/10 16:39:37 southa Exp $
 * $Log: CoreInterpreter.cpp,v $
 * Revision 1.4  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreInterpreter.h"
#include "CoreCommandHandler.h"
#include "CoreException.h"

CoreInterpreter *CoreInterpreter::m_instance = NULL;

CoreScalar
CoreInterpreter::Execute(CoreCommand& ioCommand)
{
    CoreScalar retScalar(0);
    if (m_handlers.find(ioCommand.Name()) != m_handlers.end())
    {
        try
        {
            retScalar=m_handlers[ioCommand.Name()](ioCommand, CoreEnv::Instance());
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
