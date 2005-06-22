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
 * $Id: MushGameLinkLocal.cpp,v 1.2 2005/06/21 15:57:48 southa Exp $
 * $Log: MushGameLinkLocal.cpp,v $
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameLinkLocal.h"

#include "MushGameUtil.h"

MushGameLinkLocal::tPipeData MushGameLinkLocal::m_pipeData;

MushGameLinkLocal::MushGameLinkLocal() :
    m_uplinkRef("", m_pipeData),
    m_downlinkRef("", m_pipeData)
{    
}

void
MushGameLinkLocal::SrcDestSet(const std::string& inSrcName, const std::string& inDestName)
{
    MushGameLink::SrcDestSet(inSrcName, inDestName);
    // Touch the data objects to create them
    m_pipeData.GetOrCreate(inSrcName);
    m_pipeData.GetOrCreate(inDestName);
    m_uplinkRef.NameSet(inSrcName);
    m_downlinkRef.NameSet(inDestName);
}

bool
MushGameLinkLocal::OutboxSendUnlessEmpty(void)
{
    bool isEmpty = m_outBox.IsEmpty();
    if (!isEmpty)
    {
        MushGameMailbox *pMailbox = new MushGameMailbox;
        std::swap(*pMailbox, m_outBox); // Element-wise (shallow) swap
        m_uplinkRef.WRef().Give(pMailbox);
    }
    return isEmpty;
}

bool
MushGameLinkLocal::InboxGet(MushGameMailbox& outMailbox)
{
    MushGameMailbox *pMailbox = NULL;
    bool isEmpty = !m_downlinkRef.WRef().TopGet(pMailbox);
    if (!isEmpty)
    {
        std::swap(outMailbox, *pMailbox); // Element-wise (shallow) swap
        m_downlinkRef.WRef().TopDelete();
    }
    return isEmpty;
}    

void 
MushGameLinkLocal::ToOutboxCopy(const MushGameMessage& inMessage)
{
    MushGameMessage *pMessage = dynamic_cast<MushGameMessage *>(inMessage.AutoClone());
    if (pMessage == NULL)
    {
        throw MushcoreLogicFail("MushGameLinkLocal::CopyAndSend catastrophe");
    }
    m_outBox.Give(pMessage);
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
}
//%outOfLineFunctions } DYtFqmdXUuZoTSDRQ32IcQ
