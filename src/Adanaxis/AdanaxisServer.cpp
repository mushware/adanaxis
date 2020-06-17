//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisServer.cpp
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
//%Header } r7ymYxnOqcvsMLCwo+xrJw
/*
 * $Id: AdanaxisServer.cpp,v 1.9 2007/04/18 09:22:04 southa Exp $
 * $Log: AdanaxisServer.cpp,v $
 * Revision 1.9  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.8  2006/08/01 17:21:29  southa
 * River demo
 *
 * Revision 1.7  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/23 13:56:57  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/22 20:01:57  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/21 15:57:46  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:49:57  southa
 * Client/server work
 *
 */

#include "AdanaxisServer.h"

void
AdanaxisServer::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    MushGameServer::MessageConsume(ioLogic, inMessage);
}

//%outOfLineFunctions {

const char *AdanaxisServer::AutoName(void) const
{
    return "AdanaxisServer";
}

MushcoreVirtualObject *AdanaxisServer::AutoClone(void) const
{
    return new AdanaxisServer(*this);
}

MushcoreVirtualObject *AdanaxisServer::AutoCreate(void) const
{
    return new AdanaxisServer;
}

MushcoreVirtualObject *AdanaxisServer::AutoVirtualFactory(void)
{
    return new AdanaxisServer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisServer", AdanaxisServer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisServer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameServer::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisServer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameServer::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisServer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameServer::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 6ZhKK88QgMUPxqzwtFIPJQ
