//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameServer.cpp
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
//%Header } JZ0PtblY1nZ0noWsq020yA
/*
 * $Id: MushGameServer.cpp,v 1.5 2006/06/01 15:39:27 southa Exp $
 * $Log: MushGameServer.cpp,v $
 * Revision 1.5  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameServer.h"

#include "MushGameMessageJoinRequest.h"

MUSHCORE_DATA_INSTANCE(MushGameServer);

MushGameServer::MushGameServer()
{
}

void
MushGameServer::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageJoinRequest *joinRequest = dynamic_cast<const MushGameMessageJoinRequest *>(&inMessage);
    if (joinRequest != NULL)
    {
        JoinRequestConsume(ioLogic, inMessage);
    }
    else
    {
        throw MushcoreDataFail(std::string("Unhandled message type ")+inMessage.AutoName());
    }
}

void
MushGameServer::JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("No handler provided for ")+inMessage.AutoName());
}

//%outOfLineFunctions {

const char *MushGameServer::AutoName(void) const
{
    return "MushGameServer";
}

MushcoreVirtualObject *MushGameServer::AutoClone(void) const
{
    return new MushGameServer(*this);
}

MushcoreVirtualObject *MushGameServer::AutoCreate(void) const
{
    return new MushGameServer;
}

MushcoreVirtualObject *MushGameServer::AutoVirtualFactory(void)
{
    return new MushGameServer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameServer", MushGameServer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameServer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "saveDataRef=" << m_saveDataRef;
    ioOut << "]";
}
bool
MushGameServer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "saveDataRef")
    {
        ioIn >> m_saveDataRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameServer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
}
//%outOfLineFunctions } aL8z7J6gC/6orBtWxaTU0g
