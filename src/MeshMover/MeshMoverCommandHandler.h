//%includeGuardStart {
#ifndef MESHMOVERCOMMANDHANDLER_H
#define MESHMOVERCOMMANDHANDLER_H
//%includeGuardStart } 1gLLi0dvti8YYY/BbmE7VQ
//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverCommandHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lTUP8ZLoWGMhLKR4xEKccQ
/*
 * $Id: MeshMoverCommandHandler.h,v 1.2 2004/01/02 21:13:10 southa Exp $
 * $Log: MeshMoverCommandHandler.h,v $
 * Revision 1.2  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "mushMushcore.h"

class MeshMoverCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar MeshMover(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
