//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenCommandHandler.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 04ibjznWyMrhrHyAwK+G8A
/*
 * $Id: MaurheenCommandHandler.cpp,v 1.1 2004/03/06 14:01:42 southa Exp $
 * $Log: MaurheenCommandHandler.cpp,v $
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
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
