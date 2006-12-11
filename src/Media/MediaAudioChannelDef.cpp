//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioChannelDef.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } x4lGD8QS4IQs4NaFlJyuRA
/*
 * $Id$
 * $Log$
 */

#include "MediaAudioChannelDef.h"

MediaAudioChannelDef::MediaAudioChannelDef() :
    m_activity(kActivityIdle),
    m_positional(false)
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
    ioOut << "positional=" << m_positional;
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
}
//%outOfLineFunctions } WJDBG60eaa6DdqZ9GFVgIQ
