//%includeGuardStart {
#ifndef INFERNALCOMMANDHANDLER_H
#define INFERNALCOMMANDHANDLER_H
//%includeGuardStart } +swOa2OZIERoGJVA5ouMHA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } r0JNBhRFJkXxSnx0KE1UWg
/*
 * $Id: InfernalCommandHandler.h,v 1.1 2003/10/04 15:32:10 southa Exp $
 * $Log: InfernalCommandHandler.h,v $
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */
#include "Mushcore.h"

class InfernalCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar Infernal(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
