//%includeGuardStart {
#ifndef MUSHGAMERECEIVER_H
#define MUSHGAMERECEIVER_H
//%includeGuardStart } guivrlPkjjvW1opalnnA8w
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameReceiver.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 5iETz5j8OX6vjuLqntqgIg
/*
 * $Id: MushGameReceiver.h,v 1.3 2006/06/01 15:39:26 southa Exp $
 * $Log: MushGameReceiver.h,v $
 * Revision 1.3  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"

class MushGameLogic;

class MushGameReceiver
{
public:
	virtual ~MushGameReceiver() {}
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage) = 0;
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
