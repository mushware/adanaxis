/*
 * $Id: MustlAddress.cpp,v 1.2 2002/11/28 12:05:45 southa Exp $
 * $Log: MustlAddress.cpp,v $
 * Revision 1.2  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.1  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 */

#include "MustlAddress.h"

#include "MustlUtils.h"
#include "MediaSDL.h"

#include "mushPlatform.h"

void
MustlAddress::Print(ostream& ioOut) const
{
    ioOut << MustlUtils::IPAddressToLogString(m_ip) << ":" << PlatformNet:: NetworkToHostOrderU16(m_port);
}

string
MustlAddress::HostStringGet(void) const
{
    return MustlUtils::IPAddressToString(m_ip);
}

U32
MustlAddress::PortGetHostOrder(void) const
{
    return PlatformNet::NetworkToHostOrderU16(m_port);
}

void
MustlAddress::ResolveFrom(const string& inHost, U32 inPortHostOrder)
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
