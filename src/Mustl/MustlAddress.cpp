//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlAddress.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } rXSzMyZJGgREp5God04GkQ
/*
 * $Id: MustlAddress.cpp,v 1.12 2006/06/01 15:39:49 southa Exp $
 * $Log: MustlAddress.cpp,v $
 * Revision 1.12  2006/06/01 15:39:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.10  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:20  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.6  2003/01/16 15:58:01  southa
 * Mustl exception handling
 *
 * Revision 1.5  2002/12/29 20:59:58  southa
 * More build fixes
 *
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
    ioOut << MustlUtils::IPAddressToString(m_ip) << ":" << MustlPlatform:: NetworkToHostOrderU16(m_port);
}

string
MustlAddress::StringGet(void) const
{
    ostringstream message;
    message << MustlUtils::IPAddressToString(m_ip) << ":" << MustlPlatform:: NetworkToHostOrderU16(m_port);
    return message.str();
}

string
MustlAddress::LogStringGet(void) const
{
    ostringstream message;
    message << MustlUtils::IPAddressToLogString(m_ip) << ":" << MustlPlatform:: NetworkToHostOrderU16(m_port);
    return message.str();
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
