/*
 * $Id$
 * $Log$
 */

#include "MediaNetAddress.h"

#include "MediaNetUtils.h"

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
