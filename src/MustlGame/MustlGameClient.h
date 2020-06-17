//%includeGuardStart {
#ifndef MUSTLGAMECLIENT_H
#define MUSTLGAMECLIENT_H
//%includeGuardStart } DO38GxdpzP7KsHAjEqyJJA
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameClient.h
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
//%Header } BoErN4723YwTepbQPhmbvg
/*
 * $Id: MustlGameClient.h,v 1.8 2006/06/01 20:13:01 southa Exp $
 * $Log: MustlGameClient.h,v $
 * Revision 1.8  2006/06/01 20:13:01  southa
 * Initial texture caching
 *
 * Revision 1.7  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.21  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.20  2003/10/04 12:44:33  southa
 * File renaming
 *
 * Revision 1.19  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.18  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.17  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.16  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.15  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.10  2002/12/07 18:32:14  southa
 * Network ID stuff
 *
 * Revision 1.9  2002/12/05 23:52:51  southa
 * Network management and status
 *
 * Revision 1.8  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.7  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.6  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.5  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.4  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.2  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 */

#include "mushMushcore.h"

#include "MustlAddress.h"
#include "MustlData.h"
#include "MustlLink.h"
#include "MustlGameBase.h"

class InfernalPiecePlayer;

#include "mushMedia.h"

class MustlGameClient : public MustlGameBase
{
public:
    explicit MustlGameClient(const std::string& inName);
    virtual void Ticker(const std::string& inName);
    virtual void WebPrint(std::ostream& ioOut) const;
    
    void JoinGame(const std::string& inServer, Mushware::U32 inPort);
    void AddressSet(MustlAddress& inAddress) { m_netAddress = inAddress; }
    const std::string& PlayerNameGet(void) const { return m_playerName; }
    void PlayerNameSet(const std::string& inPlayerName) { m_playerName = inPlayerName; }
    const MustlAddress& AddressGet(void) const { return m_netAddress; }
    
    void Kill(void);
    bool IsDead(void) const { return m_killed; }
    void UpdateStatus(void);
    void ReliableSendToServer(MustlData& ioData);
    void FastSendToServer(MustlData& ioData);
    
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    static void WebHeaderPrint(std::ostream& ioOut);
    
protected:
    void UpdateServer(void);
        
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleGameDefClientEnd(MushcoreXML& inXML);
    void HandleULBytesEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<std::string, void (MustlGameClient::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    Mushware::U32 m_baseThreaded;
    
    enum
    {
        kRegistrationMsec=10000,
        kServerTimeoutMsec=5000,
        kNumSetupModeLinks=1,
        kNumGameModeLinks=2,
        kMaxLinks=2
    };

    Mushware::U32 m_lastLinkMsec;
    Mushware::U32 m_lastRegistrationMsec;
    Mushware::U32 m_currentMsec;
    std::string m_serverName;
    std::string m_playerName;
    MustlAddress m_netAddress;
    std::vector< MushcoreDataRef<MustlLink> > m_netLinks;
    Mushware::U32 m_lastLinkNum;
    Mushware::U32 m_numLinks;
    Mushware::U32 m_uplinkBandwidth;
    bool m_killed;
    bool m_joined;
    bool m_linkGood;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
