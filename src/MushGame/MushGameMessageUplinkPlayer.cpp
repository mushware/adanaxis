//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPlayer.cpp
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
//%Header } BPg94ynwiRBU5EXAu4KDdw
/*
 * $Id: MushGameMessageUplinkPlayer.cpp,v 1.2 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageUplinkPlayer.cpp,v $
 * Revision 1.2  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/11 14:48:46  southa
 * Uplink work
 *
 */

#include "MushGameMessageUplinkPlayer.h"

//%outOfLineFunctions {

const char *MushGameMessageUplinkPlayer::AutoName(void) const
{
    return "MushGameMessageUplinkPlayer";
}

MushcoreVirtualObject *MushGameMessageUplinkPlayer::AutoClone(void) const
{
    return new MushGameMessageUplinkPlayer(*this);
}

MushcoreVirtualObject *MushGameMessageUplinkPlayer::AutoCreate(void) const
{
    return new MushGameMessageUplinkPlayer;
}

MushcoreVirtualObject *MushGameMessageUplinkPlayer::AutoVirtualFactory(void)
{
    return new MushGameMessageUplinkPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageUplinkPlayer", MushGameMessageUplinkPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageUplinkPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessageUplinkPiece::AutoPrint(ioOut);
    ioOut << "fireState=" << m_fireState;
    ioOut << "]";
}
bool
MushGameMessageUplinkPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "fireState")
    {
        ioIn >> m_fireState;
    }
    else if (MushGameMessageUplinkPiece::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageUplinkPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessageUplinkPiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("fireState");
    ioOut << m_fireState;
}
//%outOfLineFunctions } PL+NHARGaBgcMClIrHxIew
