//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLinkLocal.cpp
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
//%Header } Fj6DJ9Nl9r0XWjQ8VWoIog
/*
 * $Id: MushGameLinkLocal.cpp,v 1.1 2005/06/20 16:14:31 southa Exp $
 * $Log: MushGameLinkLocal.cpp,v $
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameLinkLocal.h"

#include "MushGameUtil.h"

void 
MushGameLinkLocal::MessagesPump(MushGameLogic& ioLogic)
{
    // FIXME: Reply routing
    MushGameMailbox *pMailbox;
    
    while (m_clientToServer.TopGet(pMailbox))
    {
        MushGameUtil::MailboxToServerMove(m_serverRef.WRef(), *pMailbox, ioLogic);
        m_clientToServer.TopDelete();
    }

    while (m_serverToClient.TopGet(pMailbox))
    {
        MushGameUtil::MailboxToClientMove(m_clientRef.WRef(), *pMailbox, ioLogic);
        m_serverToClient.TopDelete();
    }
}

//%outOfLineFunctions {

const char *MushGameLinkLocal::AutoName(void) const
{
    return "MushGameLinkLocal";
}

MushcoreVirtualObject *MushGameLinkLocal::AutoClone(void) const
{
    return new MushGameLinkLocal(*this);
}

MushcoreVirtualObject *MushGameLinkLocal::AutoCreate(void) const
{
    return new MushGameLinkLocal;
}

MushcoreVirtualObject *MushGameLinkLocal::AutoVirtualFactory(void)
{
    return new MushGameLinkLocal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLinkLocal", MushGameLinkLocal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLinkLocal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameLink::AutoPrint(ioOut);
    ioOut << "clientRef=" << m_clientRef << ", ";
    ioOut << "serverRef=" << m_serverRef << ", ";
    ioOut << "]";
}
bool
MushGameLinkLocal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "clientRef")
    {
        ioIn >> m_clientRef;
    }
    else if (inTagStr == "serverRef")
    {
        ioIn >> m_serverRef;
    }
    else if (MushGameLink::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameLinkLocal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameLink::AutoXMLPrint(ioOut);
    ioOut.TagSet("clientRef");
    ioOut << m_clientRef;
    ioOut.TagSet("serverRef");
    ioOut << m_serverRef;
}
//%outOfLineFunctions } JGEt7I08j1ssgyv3n/GnMg
