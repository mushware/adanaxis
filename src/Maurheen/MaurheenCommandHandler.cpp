//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenCommandHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ckVzEF6Ye9pFkyW9qufGrw
/*
 * $Id: MaurheenCommandHandler.cpp,v 1.4 2004/01/06 20:46:51 southa Exp $
 * $Log: MaurheenCommandHandler.cpp,v $
 */

#include "MaurheenCommandHandler.h"

#include "MaurheenAppHandler.h"
#include "MaurheenInfo.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MaurheenCommandHandlerInstaller(MaurheenCommandHandler::Install);

MushcoreScalar
MaurheenCommandHandler::Maurheen(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreInfo::SingletonMutate(new MaurheenInfo);

    MaurheenAppHandler *pAppHandler = new MaurheenAppHandler;
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);
    pAppHandler->GameModeEnter(false);
    
    return MushcoreScalar(0);
}

void
MaurheenCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("maurheen", Maurheen);
}
