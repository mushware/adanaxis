//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPiece.cpp
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
//%Header } 5adTpcLSepe6N2AeRcR+Cg
/*
 * $Id: MushGameMessageUplinkPiece.cpp,v 1.2 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageUplinkPiece.cpp,v $
 * Revision 1.2  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/11 14:48:46  southa
 * Uplink work
 *
 */

#include "MushGameMessageUplinkPiece.h"

//%outOfLineFunctions {

const char *MushGameMessageUplinkPiece::AutoName(void) const
{
    return "MushGameMessageUplinkPiece";
}

MushcoreVirtualObject *MushGameMessageUplinkPiece::AutoClone(void) const
{
    return new MushGameMessageUplinkPiece(*this);
}

MushcoreVirtualObject *MushGameMessageUplinkPiece::AutoCreate(void) const
{
    return new MushGameMessageUplinkPiece;
}

MushcoreVirtualObject *MushGameMessageUplinkPiece::AutoVirtualFactory(void)
{
    return new MushGameMessageUplinkPiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageUplinkPiece", MushGameMessageUplinkPiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageUplinkPiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "post=" << m_post;
    ioOut << "]";
}
bool
MushGameMessageUplinkPiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameMessageUplinkPiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("post");
    ioOut << m_post;
}
//%outOfLineFunctions } HtOAg/6FUltTRUu64NMpaQ
