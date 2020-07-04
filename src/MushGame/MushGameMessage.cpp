//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessage.cpp
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
//%Header } a+VwjsAKKLKRGjzNLH1mwQ
/*
 * $Id: MushGameMessage.cpp,v 1.7 2006/06/01 15:39:23 southa Exp $
 * $Log
 */

#include "MushGameMessage.h"

Mushware::S32 MushGameMessage::m_instanceCounter = 0;

//%outOfLineFunctions {

const char *MushGameMessage::AutoName(void) const
{
    return "MushGameMessage";
}

MushcoreVirtualObject *MushGameMessage::AutoClone(void) const
{
    return new MushGameMessage(*this);
}

MushcoreVirtualObject *MushGameMessage::AutoCreate(void) const
{
    return new MushGameMessage;
}

MushcoreVirtualObject *MushGameMessage::AutoVirtualFactory(void)
{
    return new MushGameMessage;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessage", MushGameMessage::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessage::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "srcAddrRef=" << m_srcAddrRef << ", ";
    ioOut << "id=" << m_id;
    ioOut << "]";
}
bool
MushGameMessage::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameMessage::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("id");
    ioOut << m_id;
}
//%outOfLineFunctions } bD9TYqfQLqtbsUeThpAL1Q
