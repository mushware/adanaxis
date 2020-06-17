//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDigest.cpp
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
//%Header } 1K8HvjoYPhZ40qjEeMg+nA
/*
 * $Id: MushGameDigest.cpp,v 1.5 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameDigest.cpp,v $
 * Revision 1.5  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
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

#include "MushGameDigest.h"

MushGameDigest::MushGameDigest()
{
}

void
MushGameDigest::Give(MushGameMessage *iopMessage)
{
    m_deque.push_back(iopMessage);
    //iopMessage = NULL;
}

bool
MushGameDigest::TakeIfAvailable(MushGameMessage *& iopMessage)
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

//%outOfLineFunctions {

const char *MushGameDigest::AutoName(void) const
{
    return "MushGameDigest";
}

MushcoreVirtualObject *MushGameDigest::AutoClone(void) const
{
    return new MushGameDigest(*this);
}

MushcoreVirtualObject *MushGameDigest::AutoCreate(void) const
{
    return new MushGameDigest;
}

MushcoreVirtualObject *MushGameDigest::AutoVirtualFactory(void)
{
    return new MushGameDigest;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameDigest", MushGameDigest::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameDigest::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "digestID=" << m_digestID << ", ";
    ioOut << "deque=" << m_deque;
    ioOut << "]";
}
bool
MushGameDigest::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "digestID")
    {
        ioIn >> m_digestID;
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
MushGameDigest::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("digestID");
    ioOut << m_digestID;
    ioOut.TagSet("deque");
    ioOut << m_deque;
}
//%outOfLineFunctions } Q8eQWtAKCXjOR0zaKJkNAw
