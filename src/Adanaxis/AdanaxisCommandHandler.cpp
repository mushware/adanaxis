//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisCommandHandler.cpp
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
//%Header } QR0UCT6QeReDIX3KBuPn+w
/*
 * $Id: AdanaxisCommandHandler.cpp,v 1.3 2005/06/03 13:36:44 southa Exp $
 * $Log: AdanaxisCommandHandler.cpp,v $
 */

#include "AdanaxisCommandHandler.h"

#include "AdanaxisAppHandler.h"
#include "AdanaxisInfo.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller AdanaxisCommandHandlerInstaller(AdanaxisCommandHandler::Install);

MushcoreScalar
AdanaxisCommandHandler::Adanaxis(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreInfo::SingletonMutate(new AdanaxisInfo);

    AdanaxisAppHandler *pAppHandler = new AdanaxisAppHandler;
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);
    
    return MushcoreScalar(0);
}

void
AdanaxisCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("adanaxis", Adanaxis);
}
