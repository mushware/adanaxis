//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioChannelDef.cpp
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
//%Header } ooI1EEYMYDGInJff+oXCrA
/*
 * $Id: MediaAudioChannelDef.cpp,v 1.2 2006/12/11 15:01:47 southa Exp $
 * $Log: MediaAudioChannelDef.cpp,v $
 * Revision 1.2  2006/12/11 15:01:47  southa
 * Snapshot
 *
 * Revision 1.1  2006/12/11 13:28:23  southa
 * Snapshot
 *
 */

#include "MediaAudioChannelDef.h"

MediaAudioChannelDef::MediaAudioChannelDef() :
    m_activity(kActivityIdle),
    m_positional(false),
    m_loop(false),
    m_voice(false)
{    
}

//%outOfLineFunctions {

const char *MediaAudioChannelDef::AutoName(void) const
{
    return "MediaAudioChannelDef";
}

MushcoreVirtualObject *MediaAudioChannelDef::AutoClone(void) const
{
    return new MediaAudioChannelDef(*this);
}

MushcoreVirtualObject *MediaAudioChannelDef::AutoCreate(void) const
{
    return new MediaAudioChannelDef;
}

MushcoreVirtualObject *MediaAudioChannelDef::AutoVirtualFactory(void)
{
    return new MediaAudioChannelDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MediaAudioChannelDef", MediaAudioChannelDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MediaAudioChannelDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "activity=" << m_activity << ", ";
    ioOut << "volume=" << m_volume << ", ";
    ioOut << "position=" << m_position << ", ";
    ioOut << "positional=" << m_positional << ", ";
    ioOut << "loop=" << m_loop << ", ";
    ioOut << "voice=" << m_voice;
    ioOut << "]";
}
bool
MediaAudioChannelDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "activity")
    {
        ioIn >> m_activity;
    }
    else if (inTagStr == "volume")
    {
        ioIn >> m_volume;
    }
    else if (inTagStr == "position")
    {
        ioIn >> m_position;
    }
    else if (inTagStr == "positional")
    {
        ioIn >> m_positional;
    }
    else if (inTagStr == "loop")
    {
        ioIn >> m_loop;
    }
    else if (inTagStr == "voice")
    {
        ioIn >> m_voice;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MediaAudioChannelDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("activity");
    ioOut << m_activity;
    ioOut.TagSet("volume");
    ioOut << m_volume;
    ioOut.TagSet("position");
    ioOut << m_position;
    ioOut.TagSet("positional");
    ioOut << m_positional;
    ioOut.TagSet("loop");
    ioOut << m_loop;
    ioOut.TagSet("voice");
    ioOut << m_voice;
}
//%outOfLineFunctions } UdoixiBSWyzNPSeltHefvQ
