/*
 * $Id: MediaNetLink.cpp,v 1.4 2002/11/03 18:43:09 southa Exp $
 * $Log: MediaNetLink.cpp,v $
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

#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

auto_ptr< CoreData<MediaNetLink> > CoreData<MediaNetLink>::m_instance;

MediaNetLink::MediaNetLink(const string& inServer, U32 inPort)
{
    // I am the client end of the link
    Initialise();
    TCPConnect(inServer, inPort);
    UDPConnect(inPort);
    m_client.UDPRemotePortSet(inPort);
    RequestLinkChecks();
}

MediaNetLink::MediaNetLink(TCPsocket inSocket, U32 inPort)
{
    // I am the server end of the link
    Initialise();
    TCPSocketTake(inSocket);
    m_client.UDPRemotePortSet(0);
    m_udpState.linkState=kLinkStateUseServer;
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
}

MediaNetLink::~MediaNetLink()
{
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
        case kLinkStateUseServer:
            return true;
    }
    COREASSERT(false);
    return false;
}

void
MediaNetLink::RequestLinkChecks(void)
{
    m_currentMsec=SDL_GetTicks();
    {
        MediaNetData data;
        BuildLinkCheck(data, m_tcpState);
        TCPSend(data);
    }
    {
        MediaNetData data;
        BuildLinkCheck(data, m_udpState);
        UDPSend(data);
    }
}    

void
MediaNetLink::BuildLinkCheck(MediaNetData& outData, LinkState& ioState)
{
    ioState.linkCheckSeqNum++;
    MediaNetProtocol::LinkCheckCreate(outData, ioState.linkCheckSeqNum);
    ioState.linkCheckState=kLinkCheckStateAwaitingReply;
    ioState.linkCheckTime=m_currentMsec;
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
    if (m_udpState.linkState == kLinkStateUseServer)
    {
        cerr << "Sending via server; client=" << m_client << endl;
        MediaNetServer::Instance().UDPSend(m_client.UDPRemoteIPGet(), m_client.UDPRemotePortGet(), ioData);
    }
    else
    {
        m_client.UDPSend(ioData);
    }
    cerr << endl << "*** Using client " << m_client << endl;
    cerr << "Sent " << ioData << " to " << MediaNetUtils::IPAddressToString(m_client.UDPRemoteIPGet()) << ":" << m_client.UDPRemotePortGet() << endl << endl; 
}

void
MediaNetLink::UDPReceive(MediaNetData& outData)
{
    if (!LinkIsUp(m_udpState.linkState))
    {
        // UDPLinkMake();
        COREASSERT(false);
    }
    if (m_udpState.linkState == kLinkStateUseServer)
    {
        U32 host, port;
        MediaNetServer::Instance().UDPReceive(host, port, outData);
        outData.SourceSet(host, port);
        // cerr << "Received on " << MediaNetUtils::IPAddressToString(host) << ":" << port << ": " << outData << endl;
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
    UDPReceive(m_udpState.data);
    if (!m_udpState.data.IsEmptyForRead())
    {
        MediaNetProtocol::Unpack(m_udpState.data);
        if (MediaNetProtocol::MessageTake(m_udpState.data))
        {
            outData = &m_udpState.data;
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
        case MediaNetProtocol::kMessageTypeLinkCheck:
            MessageLinkCheckHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeLinkCheckReply:
            MessageLinkCheckReplyHandle(ioData);
            break;

        default:
            break;
    }
}

void
MediaNetLink::MessageLinkCheckHandle(MediaNetData& ioData)
{
    U8 seqNum = ioData.MessageBytePop();
    if (!m_client.UDPConnectedGet())
    {
        UDPConnect(ioData.SourcePortGet());
        m_udpState.linkState=kLinkStateUntested;
    }
    // This needs analysing
    m_client.UDPRemotePortSet(ioData.SourcePortGet());

    MediaNetData replyData;
    MediaNetProtocol::LinkCheckReplyCreate(replyData, seqNum);
    UDPSend(replyData);

    if (m_udpState.linkState == kLinkStateUntested)
    {
        RequestLinkChecks();
    }
}

void
MediaNetLink::MessageLinkCheckReplyHandle(MediaNetData& ioData)
{
    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_udpState.linkCheckSeqNum)
    {
        cerr << "Received valid UDP link check reply" << endl;
        if (m_udpState.linkState == kLinkStateUntested)
        {
            m_udpState.linkState = kLinkStateIdle;
        }
        m_udpState.linkCheckState = kLinkCheckStateIdle;
    }
}

void
MediaNetLink::Print(ostream& ioOut) const
{
    ioOut << "[tcpState=" << m_tcpState << ", udpState=" << m_udpState << ", targetIsServer=" << m_targetIsServer;
    ioOut << ", client=" << m_client << "]";
}
