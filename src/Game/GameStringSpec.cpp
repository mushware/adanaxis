//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameStringSpec.cpp
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
//%Header } 0/ifw6uHugXinF6XcjI9bQ
/*
 * $Id: GameStringSpec.cpp,v 1.7 2006/06/01 15:39:00 southa Exp $
 * $Log: GameStringSpec.cpp,v $
 * Revision 1.7  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/04 15:59:00  southa
 * Adanaxis work
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

#include "GameStringSpec.h"

GameStringSpec::GameStringSpec() :
  m_posticity(MushMeshPosticity::Identity()),
  m_startColour(GLColour(1,1,1,1)),
  m_midColour(GLColour(1,1,1,1)),
  m_endColour(GLColour(1,1,1,1)),
  m_startTime(0),
  m_endTime(0),
  m_fadeTime(0),
  m_startSize(0),
  m_midSize(0),
  m_endSize(0)
{
}

//%outOfLineFunctions {

const char *GameStringSpec::AutoName(void) const
{
    return "GameStringSpec";
}

MushcoreVirtualObject *GameStringSpec::AutoClone(void) const
{
    return new GameStringSpec(*this);
}

MushcoreVirtualObject *GameStringSpec::AutoCreate(void) const
{
    return new GameStringSpec;
}

MushcoreVirtualObject *GameStringSpec::AutoVirtualFactory(void)
{
    return new GameStringSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameStringSpec", GameStringSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameStringSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "string=" << m_string << ", ";
    ioOut << "posticity=" << m_posticity << ", ";
    ioOut << "startColour=" << m_startColour << ", ";
    ioOut << "midColour=" << m_midColour << ", ";
    ioOut << "endColour=" << m_endColour << ", ";
    ioOut << "startTime=" << m_startTime << ", ";
    ioOut << "endTime=" << m_endTime << ", ";
    ioOut << "fadeTime=" << m_fadeTime << ", ";
    ioOut << "startSize=" << m_startSize << ", ";
    ioOut << "midSize=" << m_midSize << ", ";
    ioOut << "endSize=" << m_endSize;
    ioOut << "]";
}
bool
GameStringSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "string")
    {
        ioIn >> m_string;
    }
    else if (inTagStr == "posticity")
    {
        ioIn >> m_posticity;
    }
    else if (inTagStr == "startColour")
    {
        ioIn >> m_startColour;
    }
    else if (inTagStr == "midColour")
    {
        ioIn >> m_midColour;
    }
    else if (inTagStr == "endColour")
    {
        ioIn >> m_endColour;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> m_startTime;
    }
    else if (inTagStr == "endTime")
    {
        ioIn >> m_endTime;
    }
    else if (inTagStr == "fadeTime")
    {
        ioIn >> m_fadeTime;
    }
    else if (inTagStr == "startSize")
    {
        ioIn >> m_startSize;
    }
    else if (inTagStr == "midSize")
    {
        ioIn >> m_midSize;
    }
    else if (inTagStr == "endSize")
    {
        ioIn >> m_endSize;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GameStringSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("string");
    ioOut << m_string;
    ioOut.TagSet("posticity");
    ioOut << m_posticity;
    ioOut.TagSet("startColour");
    ioOut << m_startColour;
    ioOut.TagSet("midColour");
    ioOut << m_midColour;
    ioOut.TagSet("endColour");
    ioOut << m_endColour;
    ioOut.TagSet("startTime");
    ioOut << m_startTime;
    ioOut.TagSet("endTime");
    ioOut << m_endTime;
    ioOut.TagSet("fadeTime");
    ioOut << m_fadeTime;
    ioOut.TagSet("startSize");
    ioOut << m_startSize;
    ioOut.TagSet("midSize");
    ioOut << m_midSize;
    ioOut.TagSet("endSize");
    ioOut << m_endSize;
}
//%outOfLineFunctions } g0m0lp9+h741nIHXwP02gQ
