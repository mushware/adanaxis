/*
 * $Id: MediaNetAddress.cpp,v 1.1 2002/11/27 13:23:27 southa Exp $
 * $Log: MediaNetAddress.cpp,v $
 * Revision 1.1  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 */

#include "MediaNetAddress.h"

#include "MediaNetUtils.h"
#include "MediaSDL.h"

#include "mushPlatform.h"

void
MediaNetAddress::Print(ostream& ioOut) const
{
    ioOut << MediaNetUtils::IPAddressToLogString(m_ip) << ":" << PlatformNet:: NetworkToHostOrderU16(m_port);
}

string
MediaNetAddress::HostStringGet(void) const
{
    return MediaNetUtils::IPAddressToString(m_ip);
}

U32
MediaNetAddress::PortGetHostOrder(void) const
{
    return PlatformNet::NetworkToHostOrderU16(m_port);
}

void
MediaNetAddress::ResolveFrom(const string& inHost, U32 inPortHostOrder)
{

    char buffer[strlen(inHost.c_str())+1];
    strncpy(buffer, inHost.c_str(), strlen(inHost.c_str())+1);

    IPaddress remoteIP;
    if (SDLNet_ResolveHost(&remoteIP, buffer, inPortHostOrder) == -1)
    {
        ostringstream message;
        message << "Address resolution failed for " << inHost << ":" << inPortHostOrder << ": " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }
    m_ip=remoteIP.host;
    m_port=remoteIP.port;
}
