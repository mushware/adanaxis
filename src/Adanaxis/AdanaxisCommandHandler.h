//%includeGuardStart {
#ifndef ADANAXISCOMMANDHANDLER_H
#define ADANAXISCOMMANDHANDLER_H
//%includeGuardStart } snbV+bJKTPwStcCXxQAMHg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisCommandHandler.h
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } f564YGYeceZUgmhff+8pxw
/*
 * $Id: AdanaxisCommandHandler.h,v 1.1 2005/06/13 17:34:54 southa Exp $
 * $Log: AdanaxisCommandHandler.h,v $
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "mushMushcore.h"

class AdanaxisCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar Adanaxis(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
