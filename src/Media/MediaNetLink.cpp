/*
 * $Id: MediaNetLink.cpp,v 1.6 2002/11/04 13:11:58 southa Exp $
 * $Log: MediaNetLink.cpp,v $
 * Revision 1.6  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.5  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.4  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.3  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.2  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.1  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MediaNetLink.h"

#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

auto_ptr< CoreData<MediaNetLink> > CoreData<MediaNetLink>::m_instance;

MediaNetLink::MediaNetLink(const string& inServer, U32 inPort)
{
    // I am the client end of the link
    Initialise();
    m_udpUseServerPort=false;
    TCPConnect(inServer, inPort);
    UDPConnect(inPort);
    m_client.UDPRemotePortSet(inPort);
    LinkChecksSend();
}

MediaNetLink::MediaNetLink(TCPsocket inSocket, U32 inPort)
{
    // I am the server end of the link
    Initialise();
    m_udpUseServerPort=true;
    TCPSocketTake(inSocket);
    m_client.UDPRemotePortSet(0); // We don't know yet

}

void
MediaNetLink::Initialise(void)
{
    m_tcpState.linkState=kLinkStateUntested;
    m_tcpState.linkCheckState=kLinkCheckStateIdle;
    m_tcpState.linkCheckSeqNum='A';
    m_udpState.linkState=kLinkStateUntested;
    m_udpState.linkCheckState=kLinkCheckStateIdle;
    m_udpState.linkCheckSeqNum='M';
    m_loggedLinkInfo=false;
}

MediaNetLink::~MediaNetLink()
{
    try
    {
        Disconnect();
    }
    catch (exception& e)
    {
        MediaNetLog::Instance().Log() << "~MediaNetLink exception: " << e.what() << endl;
    }
}

void
MediaNetLink::TCPConnect(const string& inServer, U32 inPort)
{
    m_client.TCPConnect(inServer, inPort);
    m_targetIsServer=true;
}

void
MediaNetLink::TCPSocketTake(TCPsocket inSocket)
{
    m_client.TCPSocketTake(inSocket);
    m_targetIsServer=false;
}

void
MediaNetLink::UDPConnect(U32 inPort)
{
    m_client.UDPConnect(inPort);
}

void
MediaNetLink::Disconnect(void)
{
    MediaNetLog::Instance().Log() << "Closed link " << *this << endl;
    m_client.TCPDisconnect();
    m_client.UDPDisconnect();
}

bool
MediaNetLink::LinkIsUp(tLinkState inState)
{
    switch (inState)
    {
        case kLinkStateInvalid:
        case kLinkStateNotMade:
        case kLinkStateDead:
            return false;
            
        case kLinkStateUntested:
        case kLinkStateIdle:
            return true;
    }
    COREASSERT(false);
    return false;
}

void
MediaNetLink::LinkChecksSend(void)
{
    TCPLinkCheckSend();
    UDPLinkCheckSend();
}

void
MediaNetLink::TCPLinkCheckSend(void)
{
    m_currentMsec=SDL_GetTicks();
    {
        MediaNetData data;
        m_tcpState.linkCheckSeqNum++;
        MediaNetProtocol::TCPLinkCheckCreate(data, m_tcpState.linkCheckSeqNum);
        m_tcpState.linkCheckState=kLinkCheckStateAwaitingReply;
        m_tcpState.linkCheckTime=m_currentMsec;
        TCPSend(data);
    }
}

void
MediaNetLink::UDPLinkCheckSend(void)
{
    m_currentMsec=SDL_GetTicks();
    {
        MediaNetData data;
        m_udpState.linkCheckSeqNum++;
        MediaNetProtocol::UDPLinkCheckCreate(data, m_udpState.linkCheckSeqNum);
        m_udpState.linkCheckState=kLinkCheckStateAwaitingReply;
        m_udpState.linkCheckTime=m_currentMsec;
        UDPSend(data);
    }
}    

void
MediaNetLink::TCPSend(MediaNetData& ioData)
{
    if (!LinkIsUp(m_tcpState.linkState))
    {
        // TCPLinkMake();
        COREASSERT(false);
    }
    m_client.TCPSend(ioData);
}

void
MediaNetLink::TCPReceive(MediaNetData& outData)
{
    if (!LinkIsUp(m_tcpState.linkState))
    {
        // TCPLinkMake();
        COREASSERT(false);
    }
    m_client.TCPReceive(outData);
}

void
MediaNetLink::UDPSend(MediaNetData& ioData)
{
    if (!LinkIsUp(m_udpState.linkState))
    {
        // UDPLinkMake();
        COREASSERT(false);
    }
    if (m_udpUseServerPort)
    {
        MediaNetServer::Instance().UDPSend(m_client.UDPRemoteIPGet(), m_client.UDPRemotePortGet(), ioData);
    }
    else
    {
        m_client.UDPSend(ioData);
    }
}

void
MediaNetLink::UDPReceive(MediaNetData& outData)
{
    if (!LinkIsUp(m_udpState.linkState))
    {
        // UDPLinkMake();
        COREASSERT(false);
    }
    if (m_udpUseServerPort)
    {
        U32 host, port;
        MediaNetServer::Instance().UDPReceive(host, port, outData);
        outData.SourceSet(host, port);
    }
    else
    {
        m_client.UDPReceive(outData);
    }
}

void
MediaNetLink::FastSend(MediaNetData& ioData)
{
    if (LinkIsUp(m_udpState.linkState))
    {
        UDPSend(ioData);
    }
    else if (LinkIsUp(m_tcpState.linkState))
    {
        TCPSend(ioData);
    }
    else
    {
        throw(NetworkFail("Send on dead link"));
    }
}

void
MediaNetLink::ReliableSend(MediaNetData& ioData)
{
    if (LinkIsUp(m_tcpState.linkState))
    {
        TCPSend(ioData);
    }    
    else if (LinkIsUp(m_udpState.linkState))
    {
        UDPSend(ioData);
    }
    else
    {
        throw(NetworkFail("Send on dead link"));
    }
}

bool
MediaNetLink::Receive(MediaNetData * & outData)
{
    UDPReceive(m_udpState.linkData);
    if (!m_udpState.linkData.IsEmptyForRead())
    {
        MediaNetProtocol::Unpack(m_udpState.linkData);
        if (MediaNetProtocol::MessageTake(m_udpState.linkData))
        {
            outData = &m_udpState.linkData;
            return true;
        }
    }
    
    TCPReceive(m_tcpState.linkData);
    if (!m_tcpState.linkData.IsEmptyForRead())
    {
        MediaNetProtocol::Unpack(m_tcpState.linkData);
        if (MediaNetProtocol::MessageTake(m_tcpState.linkData))
        {
            outData = &m_tcpState.linkData;
            return true;
        }
    }
    
    return false;
}

void
MediaNetLink::MessageHandle(U32 inType, MediaNetData& ioData)
{
    switch (inType)
    {
        case MediaNetProtocol::kMessageTypeTCPLinkCheck:
            MessageTCPLinkCheckHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeTCPLinkCheckReply:
            MessageTCPLinkCheckReplyHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeUDPLinkCheck:
            MessageUDPLinkCheckHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeUDPLinkCheckReply:
            MessageUDPLinkCheckReplyHandle(ioData);
            break;

        default:
            break;
    }
}

void
MediaNetLink::MessageTCPLinkCheckHandle(MediaNetData& ioData)
{
    U8 seqNum = ioData.MessageBytePop();
    
    MediaNetData replyData;
    MediaNetProtocol::TCPLinkCheckReplyCreate(replyData, seqNum);
    TCPSend(replyData);

    if (m_tcpState.linkState == kLinkStateUntested)
    {
        TCPLinkCheckSend();
    }
}

void
MediaNetLink::MessageTCPLinkCheckReplyHandle(MediaNetData& ioData)
{
    m_currentMsec=SDL_GetTicks();

    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_tcpState.linkCheckSeqNum &&
        m_tcpState.linkCheckState == kLinkCheckStateAwaitingReply)
    {
        m_tcpState.linkPingTime=m_currentMsec - m_tcpState.linkCheckTime;
        if (m_tcpState.linkState == kLinkStateUntested)
        {
            m_tcpState.linkState = kLinkStateIdle;
            if (m_udpState.linkState == kLinkStateIdle) LinkInfoLog();
        }
        m_tcpState.linkCheckState = kLinkCheckStateIdle;
    }
}

void
MediaNetLink::MessageUDPLinkCheckHandle(MediaNetData& ioData)
{
    U8 seqNum = ioData.MessageBytePop();
    if (!m_udpUseServerPort && !m_client.UDPConnectedGet())
    {
        UDPConnect(ioData.SourcePortGet());
        m_udpState.linkState=kLinkStateUntested;
    }

    if (m_client.UDPRemotePortGet() == 0)
    {
        m_client.UDPRemotePortSet(ioData.SourcePortGet());
    }

    MediaNetData replyData;
    MediaNetProtocol::UDPLinkCheckReplyCreate(replyData, seqNum);
    UDPSend(replyData);

    if (m_udpState.linkState == kLinkStateUntested)
    {
        UDPLinkCheckSend();
    }
}

void
MediaNetLink::MessageUDPLinkCheckReplyHandle(MediaNetData& ioData)
{
    m_currentMsec=SDL_GetTicks();

    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_udpState.linkCheckSeqNum &&
        m_udpState.linkCheckState == kLinkCheckStateAwaitingReply)
    {
        m_udpState.linkPingTime=m_currentMsec - m_udpState.linkCheckTime;
        if (m_udpState.linkState == kLinkStateUntested)
        {
            m_udpState.linkState = kLinkStateIdle;
            if (m_tcpState.linkState == kLinkStateIdle) LinkInfoLog();
        }
        m_udpState.linkCheckState = kLinkCheckStateIdle;
    }
}

void
MediaNetLink::LinkInfoLog(void) const
{
    if (!m_loggedLinkInfo)
    {
        MediaNetLog::Instance().Log() << "Link: " << *this << endl;
    }
    m_loggedLinkInfo=true;
}

void
MediaNetLink::Print(ostream& ioOut) const
{
    ioOut << "[tcpState=" << m_tcpState << ", udpState=" << m_udpState << ", targetIsServer=" << m_targetIsServer;
    ioOut << ", currentMsec=" << m_currentMsec << ", udpUseServerPort=" << m_udpUseServerPort;
    ioOut << ", client=" << m_client << "]";
}
