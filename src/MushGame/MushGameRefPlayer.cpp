//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRefPlayer.cpp
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
//%Header } UtcBQjoBxM6FcKt0s+JOWA
/*
 * $Id: MushGameRefPlayer.cpp,v 1.5 2006/10/02 17:25:06 southa Exp $
 * $Log: MushGameRefPlayer.cpp,v $
 * Revision 1.5  2006/10/02 17:25:06  southa
 * Object lookup and target selection
 *
 * Revision 1.4  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 */

#include "MushGameRefPlayer.h"

using namespace Mushware;
using namespace std;

MushGameRefPlayer::MushGameRefPlayer(Mushware::U32 inNum, MushcoreMaptor<MushGamePiecePlayer> *inInstance) :
    m_playerRef(*inInstance, inNum)
{
}

//%outOfLineFunctions {

const char *MushGameRefPlayer::AutoName(void) const
{
    return "MushGameRefPlayer";
}

MushcoreVirtualObject *MushGameRefPlayer::AutoClone(void) const
{
    return new MushGameRefPlayer(*this);
}

MushcoreVirtualObject *MushGameRefPlayer::AutoCreate(void) const
{
    return new MushGameRefPlayer;
}

MushcoreVirtualObject *MushGameRefPlayer::AutoVirtualFactory(void)
{
    return new MushGameRefPlayer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameRefPlayer", MushGameRefPlayer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameRefPlayer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameRef::AutoPrint(ioOut);
    ioOut << "playerRef=" << m_playerRef;
    ioOut << "]";
}
bool
MushGameRefPlayer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerRef")
    {
        ioIn >> m_playerRef;
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
MushGameRefPlayer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameRef::AutoXMLPrint(ioOut);
    ioOut.TagSet("playerRef");
    ioOut << m_playerRef;
}
//%outOfLineFunctions } 3r2e1FyW54Uq8+2Y8bl4rw
