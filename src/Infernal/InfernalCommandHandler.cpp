//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } l0nBqSn0B0wVfex1A/iasA
/*
 * $Id: InfernalCommandHandler.cpp,v 1.3 2004/01/01 23:04:02 southa Exp $
 * $Log: InfernalCommandHandler.cpp,v $
 * Revision 1.3  2004/01/01 23:04:02  southa
 * XCode fixes
 *
 * Revision 1.2  2004/01/01 21:15:45  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */

#include "InfernalCommandHandler.h"

#include "InfernalAppHandler.h"
#include "InfernalInfo.h"
#include "InfernalWebCommands.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller InfernalCommandHandlerInstaller(InfernalCommandHandler::Install);

MushcoreScalar
InfernalCommandHandler::Infernal(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Sgl().Mutate(new InfernalAppHandler);
    MushcoreInfo::SingletonMutate(new InfernalInfo);
    InfernalWebCommands::Install();
    
    return MushcoreScalar(0);
}

void
InfernalCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("infernal", Infernal);
}
