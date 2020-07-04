//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceSimple.cpp
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
//%Header } oMUvfsswJrvzQT3WUKZvNA
/*
 * $Id: MushPiePieceSimple.cpp,v 1.10 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPiePieceSimple.cpp,v $
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
 * Revision 1.5  2005/02/10 12:34:14  southa
 * Template fixes
 *
 * Revision 1.4  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.3  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.2  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.1  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 */

#include "MushPiePieceSimple.h"

//%outOfLineFunctions {

const char *MushPiePieceSimple::AutoName(void) const
{
    return "MushPiePieceSimple";
}

MushcoreVirtualObject *MushPiePieceSimple::AutoClone(void) const
{
    return new MushPiePieceSimple(*this);
}

MushcoreVirtualObject *MushPiePieceSimple::AutoCreate(void) const
{
    return new MushPiePieceSimple;
}

MushcoreVirtualObject *MushPiePieceSimple::AutoVirtualFactory(void)
{
    return new MushPiePieceSimple;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePieceSimple", MushPiePieceSimple::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPiePieceSimple::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPiePiece::AutoPrint(ioOut);
    ioOut << "pos=" << m_pos;
    ioOut << "]";
}
bool
MushPiePieceSimple::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pos")
    {
        ioIn >> m_pos;
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
MushPiePieceSimple::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPiePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("pos");
    ioOut << m_pos;
}
//%outOfLineFunctions } 8Ha57RgHInH3ZQdWoV+seg
