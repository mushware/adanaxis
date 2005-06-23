//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLink.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 3OteCOfn1xaSDLsPZcAEYQ
/*
 * $Id: MushGameLink.cpp,v 1.5 2005/06/22 20:01:58 southa Exp $
 * $Log: MushGameLink.cpp,v $
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
//%outOfLineFunctions } SLbKbkeXSvnW1IC8omftPQ
