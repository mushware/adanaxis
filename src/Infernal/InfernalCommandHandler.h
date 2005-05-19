//%includeGuardStart {
#ifndef INFERNALCOMMANDHANDLER_H
#define INFERNALCOMMANDHANDLER_H
//%includeGuardStart } +swOa2OZIERoGJVA5ouMHA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.h
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
//%Header } WswTJtrxhhTLs2AGDI8iwA
/*
 * $Id: InfernalCommandHandler.h,v 1.3 2004/01/06 20:46:50 southa Exp $
 * $Log: InfernalCommandHandler.h,v $
 * Revision 1.3  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */
#include "mushMushcore.h"

class InfernalCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar Infernal(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
