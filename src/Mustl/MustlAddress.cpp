//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlAddress.cpp
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
//%Header } x3LJitoDgFh8N4fl8I5rEg
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
