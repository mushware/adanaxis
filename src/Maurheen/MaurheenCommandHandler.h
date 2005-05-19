//%includeGuardStart {
#ifndef MAURHEENCOMMANDHANDLER_H
#define MAURHEENCOMMANDHANDLER_H
//%includeGuardStart } GJ40wkbom8hp7LYKXgFfWA
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenCommandHandler.h
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
//%Header } 7gURfSeqK2GHkqe9b8/Gfw
/*
 * $Id: MaurheenCommandHandler.h,v 1.1 2004/03/06 14:01:42 southa Exp $
 * $Log: MaurheenCommandHandler.h,v $
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
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
