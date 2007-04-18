//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDLChannelDef.cpp
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
//%Header } MskeVh2LiPSsJc3pIUsGEg
/*
 * $Id: MediaAudioSDLChannelDef.cpp,v 1.1 2006/12/11 13:28:23 southa Exp $
 * $Log: MediaAudioSDLChannelDef.cpp,v $
 * Revision 1.1  2006/12/11 13:28:23  southa
 * Snapshot
 *
 */

#include "MediaAudioSDLChannelDef.h"

MediaAudioSDLChannelDef::MediaAudioSDLChannelDef() :
    MediaAudioChannelDef(),
    m_pActiveSample(NULL)
{
    
}
//%outOfLineFunctions {

const char *MediaAudioSDLChannelDef::AutoName(void) const
{
    return "MediaAudioSDLChannelDef";
}

MushcoreVirtualObject *MediaAudioSDLChannelDef::AutoClone(void) const
{
    return new MediaAudioSDLChannelDef(*this);
}

MushcoreVirtualObject *MediaAudioSDLChannelDef::AutoCreate(void) const
{
    return new MediaAudioSDLChannelDef;
}

MushcoreVirtualObject *MediaAudioSDLChannelDef::AutoVirtualFactory(void)
{
    return new MediaAudioSDLChannelDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MediaAudioSDLChannelDef", MediaAudioSDLChannelDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MediaAudioSDLChannelDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MediaAudioChannelDef::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MediaAudioSDLChannelDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MediaAudioChannelDef::AutoXMLDataProcess(ioIn, inTagStr))
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
MediaAudioSDLChannelDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MediaAudioChannelDef::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } BvG1dqCw2MCjARW2B6LiPw
