//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLink.cpp
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
//%Header } zllDGRuatHHF1rPHRjfxgA
/*
 * $Id: MushGameLink.cpp,v 1.8 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameLink.cpp,v $
 * Revision 1.8  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.3  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameLink.h"

MUSHCORE_DATA_INSTANCE(MushGameLink);

void
MushGameLink::MessagesPump(MushGameLogic& ioLogic)
{
    // Meaningless operation for the base class
    throw MushcoreLogicFail("Pump on MushGameLink");
}

bool
MushGameLink::OutboxSendUnlessEmpty(void)
{
    // Meaningless operation for the base class
    throw MushcoreLogicFail("OutboxSendUnlessEmpty on MushGameLink");
}

bool
MushGameLink::InboxGetUnlessEmpty(MushGameMailbox& outMailbox)
{
    // Meaningless operation for the base class
    throw MushcoreLogicFail("InboxGet on MushGameLink");
}

void
MushGameLink::ToOutboxCopy(const MushGameMessage& inMessage)
{
    // Meaningless operation for the base class
    throw MushcoreLogicFail("ToOutboxAdd on MushGameLink");
}

void
MushGameLink::SrcDestSet(const std::string& inSrcName, const std::string& inDestName)
{
    m_srcAddrRef.NameSet(inSrcName);
    m_destAddrRef.NameSet(inDestName);    
}

//%outOfLineFunctions {

const char *MushGameLink::AutoName(void) const
{
    return "MushGameLink";
}

MushcoreVirtualObject *MushGameLink::AutoClone(void) const
{
    return new MushGameLink(*this);
}

MushcoreVirtualObject *MushGameLink::AutoCreate(void) const
{
    return new MushGameLink;
}

MushcoreVirtualObject *MushGameLink::AutoVirtualFactory(void)
{
    return new MushGameLink;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLink", MushGameLink::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLink::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "srcAddrRef=" << m_srcAddrRef << ", ";
    ioOut << "destAddrRef=" << m_destAddrRef;
    ioOut << "]";
}
bool
MushGameLink::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "srcAddrRef")
    {
        ioIn >> m_srcAddrRef;
    }
    else if (inTagStr == "destAddrRef")
    {
        ioIn >> m_destAddrRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameLink::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("srcAddrRef");
    ioOut << m_srcAddrRef;
    ioOut.TagSet("destAddrRef");
    ioOut << m_destAddrRef;
}
//%outOfLineFunctions } 3NEXlQSb13oG0nJ2y51KHw
