//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerCommandHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } h14k2g7Tp9SzFodUgcqYBA
/*
 * $Id$
 * $Log$
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
    pAppHandler->GameModeEnter(false);
    
    return MushcoreScalar(0);
}

void
TesseractTrainerCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("tesseracttrainer", TesseractTrainer);
}
