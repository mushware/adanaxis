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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lV8sGMPGwnqX0dD7R7A6sg
/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"

class MeshMoverCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar MeshMover(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
