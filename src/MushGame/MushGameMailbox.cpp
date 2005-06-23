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
 * $Id: MushGameMailbox.cpp,v 1.3 2005/06/20 16:14:31 southa Exp $
 * $Log: MushGameMailbox.cpp,v $
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

MushGameMailbox::~MushGameMailbox()
{
    MushGameMessage *pMessage;
    while (TakeIfAvailable(pMessage))
    {
        delete pMessage;
    }
}

void
MushGameMailbox::Give(MushGameMessage *iopMessage)
{
    m_deque.push_back(iopMessage);
    //iopMessage = NULL;
}

bool
MushGameMailbox::TakeIfAvailable(MushGameMessage *& iopMessage)
{
    bool retVal = false;
    if (!m_deque.empty())
    {
        iopMessage = m_deque.front();
        m_deque.pop_front(); // caller now owns the object
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
    ioOut << "deque=" << m_deque;
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
    else if (inTagStr == "srcAddrRef")
    {
        ioIn >> m_srcAddrRef;
    }
    else if (inTagStr == "deque")
    {
        ioIn >> m_deque;
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
}
//%outOfLineFunctions } lpcCHpO+vQnyUXaQ5XX5IA
