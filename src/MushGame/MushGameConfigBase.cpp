//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigBase.cpp
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
//%Header } dnr/HjWz49xE/KGuxKZ6BQ
/*
 * $Id: MushGameConfigBase.cpp,v 1.8 2007/09/06 19:30:34 southa Exp $
 * $Log: MushGameConfigBase.cpp,v $
 * Revision 1.8  2007/09/06 19:30:34  southa
 * Subtitles
 *
 * Revision 1.7  2007/04/16 18:51:00  southa
 * Voice work
 *
 * Revision 1.6  2006/08/01 23:21:53  southa
 * Rendering demo content
 *
 * Revision 1.5  2006/07/28 16:52:23  southa
 * Options work
 *
 * Revision 1.4  2006/07/26 16:37:23  southa
 * Options menu
 *
 * Revision 1.3  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameConfigBase.h"

using namespace Mushware;
using namespace std;

MushGameConfigBase::MushGameConfigBase()
{
    ToDefaultSet();
}

void
MushGameConfigBase::ToDefaultSet(void)
{
    m_version = 0;
    m_textureDetail = 1;
    m_audioVolume = 100;
    m_musicVolume = 100;
    m_voiceVolume = 100;
    m_safeMode = 0;
    m_mouseSensitivity = 1;
    m_brightness = 1;
    m_showSubtitles = true;
}

void
MushGameConfigBase::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    ToDefaultSet();    
}

void
MushGameConfigBase::AutoOutputPrologue(MushcoreXMLOStream& ioOut) const
{
    ioOut.OStream() << "<!-- Saved by " << MushcoreInfo::Sgl().PackageID() <<
        " " << MushcoreUtil::LogTimeString() << " -->" << endl;
}

//%outOfLineFunctions {
void
MushGameConfigBase::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "version=" << m_version << ", ";
    ioOut << "textureDetail=" << m_textureDetail << ", ";
    ioOut << "audioVolume=" << m_audioVolume << ", ";
    ioOut << "musicVolume=" << m_musicVolume << ", ";
    ioOut << "voiceVolume=" << m_voiceVolume << ", ";
    ioOut << "mouseSensitivity=" << m_mouseSensitivity << ", ";
    ioOut << "brightness=" << m_brightness << ", ";
    ioOut << "showSubtitles=" << m_showSubtitles << ", ";
    ioOut << "safeMode=" << m_safeMode;
    ioOut << "]";
}
bool
MushGameConfigBase::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "version")
    {
        ioIn >> m_version;
    }
    else if (inTagStr == "textureDetail")
    {
        ioIn >> m_textureDetail;
    }
    else if (inTagStr == "audioVolume")
    {
        ioIn >> m_audioVolume;
    }
    else if (inTagStr == "musicVolume")
    {
        ioIn >> m_musicVolume;
    }
    else if (inTagStr == "voiceVolume")
    {
        ioIn >> m_voiceVolume;
    }
    else if (inTagStr == "mouseSensitivity")
    {
        ioIn >> m_mouseSensitivity;
    }
    else if (inTagStr == "brightness")
    {
        ioIn >> m_brightness;
    }
    else if (inTagStr == "showSubtitles")
    {
        ioIn >> m_showSubtitles;
    }
    else if (inTagStr == "safeMode")
    {
        ioIn >> m_safeMode;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameConfigBase::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("version");
    ioOut << m_version;
    ioOut.TagSet("textureDetail");
    ioOut << m_textureDetail;
    ioOut.TagSet("audioVolume");
    ioOut << m_audioVolume;
    ioOut.TagSet("musicVolume");
    ioOut << m_musicVolume;
    ioOut.TagSet("voiceVolume");
    ioOut << m_voiceVolume;
    ioOut.TagSet("mouseSensitivity");
    ioOut << m_mouseSensitivity;
    ioOut.TagSet("brightness");
    ioOut << m_brightness;
    ioOut.TagSet("showSubtitles");
    ioOut << m_showSubtitles;
    ioOut.TagSet("safeMode");
    ioOut << m_safeMode;
}
//%outOfLineFunctions } SccENMkcAZWXbVe2c4GOfg
