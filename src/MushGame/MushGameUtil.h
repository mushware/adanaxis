//%includeGuardStart {
#ifndef MUSHGAMEUTIL_H
#define MUSHGAMEUTIL_H
//%includeGuardStart } Xz+VPOtIZA4jLiVZKeJwsA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 747QYibPTxsJvr7rNEv7aw
/*
 * $Id: MushGameUtil.h,v 1.12 2006/10/04 13:35:24 southa Exp $
 * $Log: MushGameUtil.h,v $
 * Revision 1.12  2006/10/04 13:35:24  southa
 * Selective targetting
 *
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
    static std::string StripFlags(std::vector<std::string> outFlags, const std::string& inString);
    
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
