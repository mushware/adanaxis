//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMailbox.cpp
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
//%Header } OMMQzGLz4W4h1E4wYjC8UA
/*
 * $Id: MushGameMailbox.cpp,v 1.8 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameMailbox.cpp,v $
 * Revision 1.8  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2006/04/11 23:30:08  southa
 * Created MushRuby from ruby-1.8.4
 *
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
