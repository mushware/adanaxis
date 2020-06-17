//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieDialogue.cpp
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
//%Header } /7RhCGauls/Y54ZHNX5TkQ
/*
 * $Id: MushPieDialogue.cpp,v 1.6 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPieDialogue.cpp,v $
 * Revision 1.6  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.2  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/10 12:34:11  southa
 * Template fixes
 *
 */

#include "MushPieDialogue.h"

using namespace Mushware;
using namespace std;

MushPieDialogue::~MushPieDialogue()
{
}

void
MushPieDialogue::Render(void) const
{
}

void
MushPieDialogue::Move(void)
{
}

void
MushPieDialogue::TextSet(Mushware::U32 inWhich, const std::string& inStr)
{
}

void
MushPieDialogue::ExpireNow()
{
}

//%outOfLineFunctions {

const char *MushPieDialogue::AutoName(void) const
{
    return "MushPieDialogue";
}

MushcoreVirtualObject *MushPieDialogue::AutoClone(void) const
{
    return new MushPieDialogue(*this);
}

MushcoreVirtualObject *MushPieDialogue::AutoCreate(void) const
{
    return new MushPieDialogue;
}

MushcoreVirtualObject *MushPieDialogue::AutoVirtualFactory(void)
{
    return new MushPieDialogue;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieDialogue", MushPieDialogue::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieDialogue::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "age=" << m_age << ", ";
    ioOut << "expired=" << m_expired;
    ioOut << "]";
}
bool
MushPieDialogue::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "age")
    {
        ioIn >> m_age;
    }
    else if (inTagStr == "expired")
    {
        ioIn >> m_expired;
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
MushPieDialogue::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("age");
    ioOut << m_age;
    ioOut.TagSet("expired");
    ioOut << m_expired;
}
//%outOfLineFunctions } Cqf8rf1BxI1wCxPudieyqg
