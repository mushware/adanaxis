//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceMobile.cpp
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
//%Header } 51Vm6CCEzw5tHBCABk5+5w
/*
 * $Id: MushPiePieceMobile.cpp,v 1.10 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPiePieceMobile.cpp,v $
 * Revision 1.10  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.8  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.6  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/10 12:34:13  southa
 * Template fixes
 *
 * Revision 1.4  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.3  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPiePieceMobile.h"

MushPiePieceMobile::MushPiePieceMobile() :
    m_currentPosIndex(0), 
    m_newPosIndex(1) 
{
}



//%outOfLineFunctions {

const char *MushPiePieceMobile::AutoName(void) const
{
    return "MushPiePieceMobile";
}

MushcoreVirtualObject *MushPiePieceMobile::AutoClone(void) const
{
    return new MushPiePieceMobile(*this);
}

MushcoreVirtualObject *MushPiePieceMobile::AutoCreate(void) const
{
    return new MushPiePieceMobile;
}

MushcoreVirtualObject *MushPiePieceMobile::AutoVirtualFactory(void)
{
    return new MushPiePieceMobile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePieceMobile", MushPiePieceMobile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPiePieceMobile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "pos0=" << m_pos0 << ", ";
    ioOut << "pos1=" << m_pos1 << ", ";
    ioOut << "currentPosIndex=" << m_currentPosIndex << ", ";
    ioOut << "newPosIndex=" << m_newPosIndex;
    ioOut << "]";
}
bool
MushPiePieceMobile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pos0")
    {
        ioIn >> m_pos0;
    }
    else if (inTagStr == "pos1")
    {
        ioIn >> m_pos1;
    }
    else if (inTagStr == "currentPosIndex")
    {
        ioIn >> m_currentPosIndex;
    }
    else if (inTagStr == "newPosIndex")
    {
        ioIn >> m_newPosIndex;
    }
    else if (MushPiePiece::AutoXMLDataProcess(ioIn, inTagStr))
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
MushPiePieceMobile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("pos0");
    ioOut << m_pos0;
    ioOut.TagSet("pos1");
    ioOut << m_pos1;
    ioOut.TagSet("currentPosIndex");
    ioOut << m_currentPosIndex;
    ioOut.TagSet("newPosIndex");
    ioOut << m_newPosIndex;
}
//%outOfLineFunctions } oVvwAulK/YSBA8a5eWW6Fw
