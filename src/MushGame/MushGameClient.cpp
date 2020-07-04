//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameClient.cpp
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
//%Header } sVDh5sgd1wZokDpTuPv9SQ
/*
 * $Id: MushGameClient.cpp,v 1.5 2006/06/01 15:39:20 southa Exp $
 * $Log: MushGameClient.cpp,v $
 * Revision 1.5  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/21 15:57:47  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameClient.h"

MUSHCORE_DATA_INSTANCE(MushGameClient);

MushGameClient::MushGameClient()
{    
}

void
MushGameClient::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
}

//%outOfLineFunctions {

const char *MushGameClient::AutoName(void) const
{
    return "MushGameClient";
}

MushcoreVirtualObject *MushGameClient::AutoClone(void) const
{
    return new MushGameClient(*this);
}

MushcoreVirtualObject *MushGameClient::AutoCreate(void) const
{
    return new MushGameClient;
}

MushcoreVirtualObject *MushGameClient::AutoVirtualFactory(void)
{
    return new MushGameClient;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameClient", MushGameClient::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameClient::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameClient::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameClient::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } cbnKsomm2pgbV/XUnmfWXw
