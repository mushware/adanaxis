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
 * $Id$
 * $Log$
  */

#include "MeshMoverCommandHandler.h"

#include "MeshMoverAppHandler.h"

#include "Mushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MeshMoverCommandHandlerInstaller(MeshMoverCommandHandler::Install);

MushcoreScalar
MeshMoverCommandHandler::MeshMover(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Sgl().Mutate(new MeshMoverAppHandler);
    return MushcoreScalar(0);
}

void
MeshMoverCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("meshmover", MeshMover);
}
