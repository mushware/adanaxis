//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.cpp
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
//%Header } 8ZH+YByKztCX9b83kDeaRA
/*
 * $Id$
 * $Log$
 */

#include "MushGameUtil.h"

void
MushGameUtil::MailboxToDigestMove(MushGameDigest& ioDigest, MushGameMailbox& ioMailbox)
{
    MushGameMessage *pMessage;
    while (ioMailbox.TakeIfAvailable(pMessage))
    {
        ioDigest.Give(pMessage);
    }
}

void
MushGameUtil::MailboxToServerMove(MushGameServer& ioServer, MushGameMailbox& ioBoxToMove, MushGameMailbox& ioReplyBox)
{
    MushGameMessage *pMessage;
    while (ioBoxToMove.TakeIfAvailable(pMessage))
    {
        ioServer.MessageConsume(ioReplyBox, *pMessage);
    }
}

void
MushGameUtil::MailboxToClientMove(MushGameClient& ioClient, MushGameMailbox& ioBoxToMove, MushGameMailbox& ioReplyBox)
{
    MushGameMessage *pMessage;
    while (ioBoxToMove.TakeIfAvailable(pMessage))
    {
        ioClient.MessageConsume(ioReplyBox, *pMessage);
    }
    
}
