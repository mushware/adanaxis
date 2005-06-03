//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerCommandHandler.cpp
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
//%Header } P8q72fYQ3IWUSGw5eVuZOQ
/*
 * $Id: TesseractTrainerCommandHandler.cpp,v 1.2 2005/05/19 13:02:21 southa Exp $
 * $Log: TesseractTrainerCommandHandler.cpp,v $
 * Revision 1.2  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/03 15:46:56  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerCommandHandler.h"

#include "TesseractTrainerAppHandler.h"
#include "TesseractTrainerInfo.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TesseractTrainerCommandHandlerInstaller(TesseractTrainerCommandHandler::Install);

MushcoreScalar
TesseractTrainerCommandHandler::TesseractTrainer(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreInfo::SingletonMutate(new TesseractTrainerInfo);

    TesseractTrainerAppHandler *pAppHandler = new TesseractTrainerAppHandler;
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);
    
    return MushcoreScalar(0);
}

void
TesseractTrainerCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("tesseracttrainer", TesseractTrainer);
}
