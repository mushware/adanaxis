/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlAddress.cpp,v 1.4 2002/12/20 13:17:45 southa Exp $
 * $Log: MustlAddress.cpp,v $
 * Revision 1.4  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/17 00:58:28  southa
 * Added support for libmustl target
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.2  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.1  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 */

#include "MustlAddress.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

void
MustlAddress::Print(ostream& ioOut) const
{
    ioOut << MustlUtils::IPAddressToLogString(m_ip) << ":" << MustlPlatform:: NetworkToHostOrderU16(m_port);
}

string
MustlAddress::HostStringGet(void) const
{
    return MustlUtils::IPAddressToString(m_ip);
}

U32
MustlAddress::PortGetHostOrder(void) const
{
    return MustlPlatform::NetworkToHostOrderU16(m_port);
}

void
MustlAddress::PortSetHostOrder(U32 inPortHostOrder)
{
    m_port = MustlPlatform::HostToNetworkOrderU16(inPortHostOrder);
}

void
MustlAddress::ResolveFromHostName(const std::string& inHostName, U32 inPortHostOrder)
{
    MustlPlatform::ResolveHostName(*this, inHostName, inPortHostOrder);
}

void
MustlAddress::ResolveFromIPAddressString(const std::string& inHostName, U32 inPortHostOrder)
{
    MustlPlatform::ResolveIPAddressString(*this, inHostName, inPortHostOrder);
}
