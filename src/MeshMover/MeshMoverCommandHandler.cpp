//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverCommandHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } BxOnlErwZmYPV94xYv3gTQ
/*
 * $Id: MeshMoverCommandHandler.cpp,v 1.1 2003/10/07 22:40:06 southa Exp $
 * $Log: MeshMoverCommandHandler.cpp,v $
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
  */

#include "MeshMoverCommandHandler.h"

#include "MeshMoverAppHandler.h"
#include "MeshMoverInfo.h"

#include "Mushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MeshMoverCommandHandlerInstaller(MeshMoverCommandHandler::Install);

MushcoreScalar
MeshMoverCommandHandler::MeshMover(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Sgl().Mutate(new MeshMoverAppHandler);
    MushcoreInfo::SingletonMutate(new MeshMoverInfo);

    return MushcoreScalar(0);
}

void
MeshMoverCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("meshmover", MeshMover);
}
