//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageFire.cpp
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
//%Header } KpoLx0skiYNUK7caz/EBaw
/*
 * $Id: MushGameMessageFire.cpp,v 1.3 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageFire.cpp,v $
 * Revision 1.3  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.1  2005/07/12 12:18:18  southa
 * Projectile work
 *
 */

#include "MushGameMessageFire.h"

//%outOfLineFunctions {

const char *MushGameMessageFire::AutoName(void) const
{
    return "MushGameMessageFire";
}

MushcoreVirtualObject *MushGameMessageFire::AutoClone(void) const
{
    return new MushGameMessageFire(*this);
}

MushcoreVirtualObject *MushGameMessageFire::AutoCreate(void) const
{
    return new MushGameMessageFire;
}

MushcoreVirtualObject *MushGameMessageFire::AutoVirtualFactory(void)
{
    return new MushGameMessageFire;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageFire", MushGameMessageFire::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageFire::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "post=" << m_post << ", ";
    ioOut << "count=" << m_count << ", ";
    ioOut << "type=" << m_type << ", ";
    ioOut << "owner=" << m_owner;
    ioOut << "]";
}
bool
MushGameMessageFire::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else if (inTagStr == "count")
    {
        ioIn >> m_count;
    }
    else if (inTagStr == "type")
    {
        ioIn >> m_type;
    }
    else if (inTagStr == "owner")
    {
        ioIn >> m_owner;
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
MushGameMessageFire::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("post");
    ioOut << m_post;
    ioOut.TagSet("count");
    ioOut << m_count;
    ioOut.TagSet("type");
    ioOut << m_type;
    ioOut.TagSet("owner");
    ioOut << m_owner;
}
//%outOfLineFunctions } dGSu6t039EO+Y26nZ3IJCA
