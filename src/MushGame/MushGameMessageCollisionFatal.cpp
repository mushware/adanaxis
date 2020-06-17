//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollisionFatal.cpp
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
//%Header } hAZzYYb7PADVOu6PcjIFbA
/*
 * $Id: MushGameMessageCollisionFatal.cpp,v 1.2 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageCollisionFatal.cpp,v $
 * Revision 1.2  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 */

#include "MushGameMessageCollisionFatal.h"

//%outOfLineFunctions {

const char *MushGameMessageCollisionFatal::AutoName(void) const
{
    return "MushGameMessageCollisionFatal";
}

MushcoreVirtualObject *MushGameMessageCollisionFatal::AutoClone(void) const
{
    return new MushGameMessageCollisionFatal(*this);
}

MushcoreVirtualObject *MushGameMessageCollisionFatal::AutoCreate(void) const
{
    return new MushGameMessageCollisionFatal;
}

MushcoreVirtualObject *MushGameMessageCollisionFatal::AutoVirtualFactory(void)
{
    return new MushGameMessageCollisionFatal;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageCollisionFatal", MushGameMessageCollisionFatal::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageCollisionFatal::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessageCollision::AutoPrint(ioOut);
    ioOut << "post1=" << m_post1 << ", ";
    ioOut << "post2=" << m_post2 << ", ";
    ioOut << "chunkNum1=" << m_chunkNum1 << ", ";
    ioOut << "chunkNum2=" << m_chunkNum2 << ", ";
    ioOut << "chunkNumsValid=" << m_chunkNumsValid;
    ioOut << "]";
}
bool
MushGameMessageCollisionFatal::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "post1")
    {
        ioIn >> m_post1;
    }
    else if (inTagStr == "post2")
    {
        ioIn >> m_post2;
    }
    else if (inTagStr == "chunkNum1")
    {
        ioIn >> m_chunkNum1;
    }
    else if (inTagStr == "chunkNum2")
    {
        ioIn >> m_chunkNum2;
    }
    else if (inTagStr == "chunkNumsValid")
    {
        ioIn >> m_chunkNumsValid;
    }
    else if (MushGameMessageCollision::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageCollisionFatal::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessageCollision::AutoXMLPrint(ioOut);
    ioOut.TagSet("post1");
    ioOut << m_post1;
    ioOut.TagSet("post2");
    ioOut << m_post2;
    ioOut.TagSet("chunkNum1");
    ioOut << m_chunkNum1;
    ioOut.TagSet("chunkNum2");
    ioOut << m_chunkNum2;
    ioOut.TagSet("chunkNumsValid");
    ioOut << m_chunkNumsValid;
}
//%outOfLineFunctions } XG0W1PQyMPpwJLRKEO3QXg
