//%includeGuardStart {
#ifndef MUSHGAMEUTIL_H
#define MUSHGAMEUTIL_H
//%includeGuardStart } Xz+VPOtIZA4jLiVZKeJwsA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.h
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
//%Header } jHsuT0DibdJl7EB6jmyAAg
/*
 * $Id: MushGameUtil.h,v 1.11 2006/09/29 10:47:56 southa Exp $
 * $Log: MushGameUtil.h,v $
 * Revision 1.11  2006/09/29 10:47:56  southa
 * Object AI
 *
 * Revision 1.10  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.9  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.7  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.6  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/23 13:56:59  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/21 15:57:48  southa
 * MushGame work
 *
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
#include "MushGameMessage.h"
#include "MushGameServer.h"

class MushGameAppHandler;
class MushGameLogic;

class MushGameUtil
{
public:
    static void MailboxToDigestMove(MushGameDigest& ioDigest, MushGameMailbox& ioMailbox);
    static void MailboxToServerMove(MushGameServer& ioServer, MushGameMailbox& ioBoxToMove, MushGameLogic& ioLogic);
    static void MailboxToClientMove(MushGameClient& ioClient, MushGameMailbox& ioBoxToMove, MushGameLogic& ioLogic);
    static std::string ObjectName(const std::string& inPrefix, const std::string& inSuffix);
    static void LocalGameCreate(const std::string& inName, const std::string& inPrefix);
    static void LocalGameJobsCreate(MushGameLogic& ioLogic);
    template <class T> static T *DataObjectCreate(const std::string& inName,
        const std::string& inPrefix, const std::string& inSuffix);
    static std::string KeyFromString(const std::string& inStr);
    static std::string KeyFromMessage(const MushGameMessage& inMessage);
    static std::string ReplyIDFromMessage(const MushGameMessage& inMessage);
    static MushGameAppHandler& AppHandler(void);
    static const MushGameLogic& LogicRef(void);
    static MushGameLogic& LogicWRef(void);
    static std::string ObjectName(const std::string& inPrefix, Mushware::U32 inNumber);
    static void ObjectNameDecode(std::string& outPrefix, Mushware::U32& outNumber, const std::string& inName);
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
