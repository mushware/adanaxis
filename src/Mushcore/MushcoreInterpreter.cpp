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
 * $Id: MushcoreInterpreter.cpp,v 1.2 2003/01/11 17:07:53 southa Exp $
 * $Log: MushcoreInterpreter.cpp,v $
 * Revision 1.2  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.10  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:45  southa
 * Conditioned source
 *
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

#include "MushcoreInterpreter.h"

#include "MushcoreCommand.h"
#include "MushcoreCommandHandler.h"
#include "MushcoreEnv.h"
#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInterpreter *MushcoreInterpreter::m_instance = NULL;

MushcoreInterpreter::MushcoreInterpreter() :
    m_logCommands(true)
{
}

void
MushcoreInterpreter::Execute(const string& inStr)
{
    MushcoreCommand command(inStr);
    command.Execute();
}

MushcoreScalar
MushcoreInterpreter::Despatch(MushcoreCommand& ioCommand)
{
    if (m_logCommands)
    {
        cerr << "Command was " << ioCommand.Name() << "(";
        cerr << ioCommand.ParamListGet() << ")" << endl;
    }
    
    MushcoreScalar retScalar(0);
    if (m_handlers.find(ioCommand.Name()) != m_handlers.end())
    {
        try
        {
            retScalar=m_handlers[ioCommand.Name()](ioCommand, MushcoreEnv::Instance());
        }
        catch (MushcoreFileFail& f)
        {
            cerr << "File operation failed: " << f.what() << endl;
        }
    }
    else
    {
        cerr << "Unknown command '" << ioCommand.Name() << "'" << endl;
    }
    return retScalar;
}

void
MushcoreInterpreter::AddHandler(const string& inName, MushcoreCommandHandler inHandler)
{
    m_handlers[inName]=inHandler;
}
