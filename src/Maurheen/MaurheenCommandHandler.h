//%includeGuardStart {
#ifndef MAURHEENCOMMANDHANDLER_H
#define MAURHEENCOMMANDHANDLER_H
//%includeGuardStart } GJ40wkbom8hp7LYKXgFfWA
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenCommandHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FxawfegyPSNcNqie12CDCQ
/*
 * $Id: MaurheenCommandHandler.h,v 1.3 2004/01/06 20:46:51 southa Exp $
 * $Log: MaurheenCommandHandler.h,v $
 */

#include "mushMushcore.h"

class MaurheenCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar Maurheen(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
