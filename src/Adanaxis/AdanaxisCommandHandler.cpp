//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisCommandHandler.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wox6rADwo6wuUXR8XLcK+w
/*
 * $Id: AdanaxisCommandHandler.cpp,v 1.6 2006/08/01 17:21:22 southa Exp $
 * $Log: AdanaxisCommandHandler.cpp,v $
 * Revision 1.6  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.5  2006/06/30 15:05:30  southa
 * Texture and buffer purge
 *
 * Revision 1.4  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
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

    AdanaxisAppHandler *pAppHandler = new AdanaxisAppHandler("adanaxis");
    
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);

    MushcoreLog::Sgl().PackageHasChanged();
    
    return MushcoreScalar(0);
}

void
AdanaxisCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("adanaxis", Adanaxis);
}
