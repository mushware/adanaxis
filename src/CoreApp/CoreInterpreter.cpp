/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: CoreInterpreter.cpp,v 1.7 2002/07/06 18:04:16 southa Exp $
 * $Log: CoreInterpreter.cpp,v $
 * Revision 1.7  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/05/30 14:41:15  southa
 * GameData and loadtilemap command
 *
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
