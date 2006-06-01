//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 1j5KwkbRdCxfovub76zRdg
/*
 * $Id: InfernalCommandHandler.cpp,v 1.5 2005/05/19 13:02:04 southa Exp $
 * $Log: InfernalCommandHandler.cpp,v $
 * Revision 1.5  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
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
