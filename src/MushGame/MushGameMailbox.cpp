//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMailbox.cpp
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
//%Header } 3fsTjKX8hwRiWKdocOfP2g
/*
 * $Id: MushGameMailbox.cpp,v 1.6 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGameMailbox.cpp,v $
 * Revision 1.6  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.5  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameMailbox.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGameMailbox);

MushGameMailbox::~MushGameMailbox()
{
    DiscardAll();
}

void
MushGameMailbox::DiscardAll(void)
{
    MushGameMessage *pMessage;
    
    while (TakeIfAvailable(pMessage))
    {
        delete pMessage;
    }
    
    m_messageCount = 0; // Just in case
}

void
MushGameMailbox::Give(MushGameMessage *iopMessage)
{
    m_deque.push_back(iopMessage);
    ++m_messageCount;
    
    if (m_messageCount > m_messageLimit)
    {
        MushcoreLog::Sgl().ErrorLog() << "Mailbox (source " << m_srcAddrRef << ") exceeded limit (" << m_messageLimit << ".  Discarding all messages" << endl;
        
        DiscardAll();
    }
}

bool
MushGameMailbox::TakeIfAvailable(MushGameMessage *& iopMessage)
{
    bool retVal = false;
    if (!m_deque.empty())
    {
        iopMessage = m_deque.front();
        m_deque.pop_front(); // caller now owns the object
        
        if (m_messageCount > 0)
        {
            --m_messageCount;
        }
        
        retVal = true;
    }
    return retVal;
}

bool
MushGameMailbox::TakeIfAvailable(std::auto_ptr<MushGameMessage>& ioaMessage)
{
    bool retVal = false;
    MushGameMessage *pMessage;
    if (TakeIfAvailable(pMessage))
    {
        ioaMessage = std::auto_ptr<MushGameMessage>(pMessage);
        retVal = true;
    }
    return retVal;;
}

//%outOfLineFunctions {

const char *MushGameMailbox::AutoName(void) const
{
    return "MushGameMailbox";
}

MushcoreVirtualObject *MushGameMailbox::AutoClone(void) const
{
    return new MushGameMailbox(*this);
}

MushcoreVirtualObject *MushGameMailbox::AutoCreate(void) const
{
    return new MushGameMailbox;
}

MushcoreVirtualObject *MushGameMailbox::AutoVirtualFactory(void)
{
    return new MushGameMailbox;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMailbox", MushGameMailbox::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMailbox::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "srcAddrRef=" << m_srcAddrRef << ", ";
    ioOut << "deque=" << m_deque << ", ";
    ioOut << "messageCount=" << m_messageCount << ", ";
    ioOut << "messageLimit=" << m_messageLimit;
    ioOut << "]";
}
bool
MushGameMailbox::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "deque")
    {
        ioIn >> m_deque;
    }
    else if (inTagStr == "messageCount")
    {
        ioIn >> m_messageCount;
    }
    else if (inTagStr == "messageLimit")
    {
        ioIn >> m_messageLimit;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameMailbox::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("deque");
    ioOut << m_deque;
    ioOut.TagSet("messageCount");
    ioOut << m_messageCount;
    ioOut.TagSet("messageLimit");
    ioOut << m_messageLimit;
}
//%outOfLineFunctions } EdFahwS2nzwyvjjVBrQuNA
