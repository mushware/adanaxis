//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nqq1CPmR9xGTAak2YjDXjg
/*
 * $Id: InfernalCommandHandler.cpp,v 1.1 2003/10/04 15:32:10 southa Exp $
 * $Log: InfernalCommandHandler.cpp,v $
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */

#include "InfernalCommandHandler.h"

#include "InfernalAppHandler.h"
#include "InfernalInfo.h"

#include "Mushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller InfernalCommandHandlerInstaller(InfernalCommandHandler::Install);

MushcoreScalar
InfernalCommandHandler::Infernal(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Sgl().Mutate(new InfernalAppHandler);
    MushcoreInfo::SingletonMutate(new InfernalInfo);

    return MushcoreScalar(0);
}

void
InfernalCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("infernal", Infernal);
}
