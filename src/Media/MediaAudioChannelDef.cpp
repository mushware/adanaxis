//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioChannelDef.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } CE9HIr03aPiTFexULC0gbQ
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
