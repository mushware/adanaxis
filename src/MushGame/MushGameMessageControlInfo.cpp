//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageControlInfo.cpp
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
//%Header } SEsckRGgwZoW2Snzmp4hMA
/*
 * $Id: MushGameMessageControlInfo.cpp,v 1.2 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageControlInfo.cpp,v $
 * Revision 1.2  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameMessageControlInfo.h"
//%outOfLineFunctions {

const char *MushGameMessageControlInfo::AutoName(void) const
{
    return "MushGameMessageControlInfo";
}

MushcoreVirtualObject *MushGameMessageControlInfo::AutoClone(void) const
{
    return new MushGameMessageControlInfo(*this);
}

MushcoreVirtualObject *MushGameMessageControlInfo::AutoCreate(void) const
{
    return new MushGameMessageControlInfo;
}

MushcoreVirtualObject *MushGameMessageControlInfo::AutoVirtualFactory(void)
{
    return new MushGameMessageControlInfo;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageControlInfo", MushGameMessageControlInfo::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageControlInfo::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "timestamp=" << m_timestamp << ", ";
    ioOut << "axisEvents=" << m_axisEvents << ", ";
    ioOut << "keyEvents=" << m_keyEvents;
    ioOut << "]";
}
bool
MushGameMessageControlInfo::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "timestamp")
    {
        ioIn >> m_timestamp;
    }
    else if (inTagStr == "axisEvents")
    {
        ioIn >> m_axisEvents;
    }
    else if (inTagStr == "keyEvents")
    {
        ioIn >> m_keyEvents;
    }
    else if (MushGameMessage::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageControlInfo::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("timestamp");
    ioOut << m_timestamp;
    ioOut.TagSet("axisEvents");
    ioOut << m_axisEvents;
    ioOut.TagSet("keyEvents");
    ioOut << m_keyEvents;
}
//%outOfLineFunctions } 2pzNQJVGzbzqSBE8BGC1KA
