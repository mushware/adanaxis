//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInterpreter.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8MAOuLpMUbLZhum+UB8pZg
/*
 * $Id: MushcoreInterpreter.cpp,v 1.11 2003/10/04 12:23:08 southa Exp $
 * $Log: MushcoreInterpreter.cpp,v $
 * Revision 1.11  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.10  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.7  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.6  2003/01/17 00:41:02  southa
 * Configuration updates from POST data
 *
 * Revision 1.5  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.4  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
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
 * InfernalData and loadtilemap command
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

#include "MushcoreBuiltinHandler.h"
#include "MushcoreCommand.h"
#include "MushcoreCommandHandler.h"
#include "MushcoreEnv.h"
#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInterpreter *MushcoreInterpreter::m_instance = NULL;

MushcoreInterpreter::MushcoreInterpreter() :
    m_logFunction(NULL)
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
    if (m_logFunction != NULL)
    {
        ostringstream message;
        message << "Command: " << ioCommand.Name() << "(" << ioCommand.ParamListGet() << ")";
        m_logFunction(message.str());
    }
    
    MushcoreScalar retScalar(0);
    tHandlerMap::const_iterator handlerFunction = m_handlers.find(ioCommand.Name());
    if (handlerFunction != m_handlers.end())
    {
        retScalar = handlerFunction->second(ioCommand, MushcoreEnv::Sgl());
    }
    else
    {
        throw(MushcoreCommandFail("Unknown command '"+ioCommand.Name()+"'"));
    }
    return retScalar;
}

void
MushcoreInterpreter::HandlerAdd(const string& inName, MushcoreCommandHandler inHandler)
{
    m_handlers[inName]=inHandler;
}

void
MushcoreInterpreter::NullFunction(void)
{
    // Ensure that the builtin handler is linked in
    MushcoreBuiltinHandler::NullFunction();
}
