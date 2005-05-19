//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverCommandHandler.cpp
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
//%Header } 6E4bMUwFogJ7oi47nBdEoA
/*
 * $Id: MeshMoverCommandHandler.cpp,v 1.4 2004/01/06 20:46:51 southa Exp $
 * $Log: MeshMoverCommandHandler.cpp,v $
 * Revision 1.4  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
  */

#include "MeshMoverCommandHandler.h"

#include "MeshMoverAppHandler.h"
#include "MeshMoverInfo.h"

#include "mushMushcore.h"
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
