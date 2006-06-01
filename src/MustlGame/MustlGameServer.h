//%includeGuardStart {
#ifndef MUSTLGAMESERVER_H
#define MUSTLGAMESERVER_H
//%includeGuardStart } 9zZoQC7qbkn9woG6KkW5iA
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameServer.h
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
//%Header } jTkRU3nq18BRvkqdj0FTpQ
/*
 * $Id: MustlGameServer.h,v 1.6 2006/06/01 15:39:57 southa Exp $
 * $Log: MustlGameServer.h,v $
 * Revision 1.6  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.15  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:43  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.12  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.11  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.9  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.7  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.6  2002/11/28 18:05:35  southa
 * Print link ages
 *
 * Revision 1.5  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.4  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.3  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.2  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 */

#include "mushMushcore.h"

#include "MustlAddress.h"
#include "MustlGameBase.h"
#include "MustlUtils.h"

#include "mushMedia.h"

class MustlGameClient;

class MustlGameServer : public MustlGameBase
{
public:
    MustlGameServer(const std::string& inName);
    virtual void Ticker(const std::string& inName);
    virtual void WebPrint(std::ostream& ioOut) const;

    void HostGame(const std::string& inContract, Mushware::U32 inPlayerLimit);
    void Kill(void);
    bool IsDead(void) const { return m_killed; }
    
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    const std::string& ServerMessageGet(void) const { return m_serverMessage; }
    void ServerMessageSet(const std::string& inMessage) { m_serverMessage = inMessage; }
    void AddressSet(MustlAddress& inAddress) { m_netAddress = inAddress; }
    const MustlAddress& AddressGet(void) const { return m_netAddress; }

    void UpdateClient(MustlGameClient& inClient);
    
protected:
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleDefServerEnd(MushcoreXML& inXML);
    void HandleMessageEnd(MushcoreXML& inXML);
    void HandleContractEnd(MushcoreXML& inXML);
    void HandlePlayerCountEnd(MushcoreXML& inXML);
    void HandlePlayerLimitEnd(MushcoreXML& inXML);
    
    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<std::string, void (MustlGameServer::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    Mushware::U32 m_baseThreaded;

    enum
    {
        kUpdateMsec=5000
    };

    void UpdateClients(void);
    
    std::string m_serverMessage;
    std::string m_contractName;
    Mushware::U32 m_playerCount;
    Mushware::U32 m_playerLimit;
    Mushware::U32 m_lastUpdateMsec;
    Mushware::U32 m_currentMsec;
    MustlAddress m_netAddress;
    bool m_killed;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
