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
 * $Id: MushGameUtil.h,v 1.2 2005/06/21 13:10:52 southa Exp $
 * $Log: MushGameUtil.h,v $
 * Revision 1.2  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
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
    static void MailboxToServerMove(MushGameServer& ioServer, MushGameMailbox& ioBoxToMove, MushGameLogic& ioLogic);
    static void MailboxToClientMove(MushGameClient& ioClient, MushGameMailbox& ioBoxToMove, MushGameLogic& ioLogic);
    static std::string ObjectName(const std::string& inPrefix, const std::string& inSuffix);
    static void LocalGameCreate(const std::string& inName, const std::string& inPrefix);
    template <class T> static T *DataObjectCreate(const std::string& inName,
        const std::string& inPrefix, const std::string& inSuffix);
private:
    
};

template <class T>
inline T *
MushGameUtil::DataObjectCreate(const std::string& inName,
    const std::string& inPrefix, const std::string& inSuffix)
{
    MushcoreData<T>::Sgl().IfExistsDelete(inName);
    MushcoreVirtualObject *pObj = MushcoreFactory::Sgl().ObjectCreate(ObjectName(inPrefix, inSuffix));
    T *pCastObj = dynamic_cast<T *>(pObj);
    if (pCastObj == NULL)
    {
        if (pObj != NULL)
        {
            delete pObj;
        }
        throw MushcoreLogicFail("Object "+ObjectName(inPrefix, inSuffix)+" is of wrong type");
    }
    MushcoreData<T>::Sgl().Give(inName, pCastObj);
    return pCastObj;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
