//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundSpec.cpp
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
//%Header } TulKV7mdA/JFNYwpwJFAmg
/*
 * $Id: GameSoundSpec.cpp,v 1.6 2006/06/01 15:39:00 southa Exp $
 * $Log: GameSoundSpec.cpp,v $
 * Revision 1.6  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.2  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.1  2005/03/25 19:13:49  southa
 * GameDialogue work
 *
 */

#include "GameSoundSpec.h"

//%outOfLineFunctions {

const char *GameSoundSpec::AutoName(void) const
{
    return "GameSoundSpec";
}

MushcoreVirtualObject *GameSoundSpec::AutoClone(void) const
{
    return new GameSoundSpec(*this);
}

MushcoreVirtualObject *GameSoundSpec::AutoCreate(void) const
{
    return new GameSoundSpec;
}

MushcoreVirtualObject *GameSoundSpec::AutoVirtualFactory(void)
{
    return new GameSoundSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameSoundSpec", GameSoundSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameSoundSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "soundRef=" << m_soundRef << ", ";
    ioOut << "startTime=" << m_startTime;
    ioOut << "]";
}
bool
GameSoundSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "soundRef")
    {
        ioIn >> m_soundRef;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> m_startTime;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GameSoundSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("soundRef");
    ioOut << m_soundRef;
    ioOut.TagSet("startTime");
    ioOut << m_startTime;
}
//%outOfLineFunctions } avBINxWjZGN7O3VJs256jA
