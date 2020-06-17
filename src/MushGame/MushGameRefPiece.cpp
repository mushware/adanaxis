//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPiece.cpp
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
//%Header } SIVvHt8CbomXFB3r+vcjOg
/*
 * $Id: MushGameRefPiece.cpp,v 1.3 2006/06/01 15:39:26 southa Exp $
 * $Log: MushGameRefPiece.cpp,v $
 * Revision 1.3  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 */

#include "MushGameRefPiece.h"

//%outOfLineFunctions {

const char *MushGameRefPiece::AutoName(void) const
{
    return "MushGameRefPiece";
}

MushcoreVirtualObject *MushGameRefPiece::AutoClone(void) const
{
    return new MushGameRefPiece(*this);
}

MushcoreVirtualObject *MushGameRefPiece::AutoCreate(void) const
{
    return new MushGameRefPiece;
}

MushcoreVirtualObject *MushGameRefPiece::AutoVirtualFactory(void)
{
    return new MushGameRefPiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRefPiece", MushGameRefPiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRefPiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameRef::AutoPrint(ioOut);
    ioOut << "pieceRef=" << m_pieceRef;
    ioOut << "]";
}
bool
MushGameRefPiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pieceRef")
    {
        ioIn >> m_pieceRef;
    }
    else if (MushGameRef::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameRefPiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameRef::AutoXMLPrint(ioOut);
    ioOut.TagSet("pieceRef");
    ioOut << m_pieceRef;
}
//%outOfLineFunctions } g3D5qPrkMolOUeAya1U8Vw
