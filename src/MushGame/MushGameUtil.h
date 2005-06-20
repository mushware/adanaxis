//%includeGuardStart {
#ifndef MUSHGAMEUTIL_H
#define MUSHGAMEUTIL_H
//%includeGuardStart } Xz+VPOtIZA4jLiVZKeJwsA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.h
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
//%Header } 18albJPuAsa/sx4nUMy3jA
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameClient.h"
#include "MushGameDigest.h"
#include "MushGameMailbox.h"
#include "MushGameServer.h"

class MushGameUtil
{
public:
    static void MailboxToDigestMove(MushGameDigest& ioDigest, MushGameMailbox& ioMailbox);
    static void MailboxToServerMove(MushGameServer& ioServer, MushGameMailbox& ioBoxToMove, MushGameMailbox& ioReplyBox);
    static void MailboxToClientMove(MushGameClient& ioClient, MushGameMailbox& ioBoxToMove, MushGameMailbox& ioReplyBox);
private:
    
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
