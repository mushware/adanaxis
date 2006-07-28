//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigBase.cpp
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
//%Header } WGW0jWLT0tHoC21nwBZAtQ
/*
 * $Id: MushGameConfigBase.cpp,v 1.4 2006/07/26 16:37:23 southa Exp $
 * $Log: MushGameConfigBase.cpp,v $
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
    m_musicVolume = 50;
    m_safeMode = 0;
    m_mouseSensitivity = 1;
    m_brightness = 1;
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
    ioOut << "mouseSensitivity=" << m_mouseSensitivity << ", ";
    ioOut << "brightness=" << m_brightness << ", ";
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
    else if (inTagStr == "mouseSensitivity")
    {
        ioIn >> m_mouseSensitivity;
    }
    else if (inTagStr == "brightness")
    {
        ioIn >> m_brightness;
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
    ioOut.TagSet("mouseSensitivity");
    ioOut << m_mouseSensitivity;
    ioOut.TagSet("brightness");
    ioOut << m_brightness;
    ioOut.TagSet("safeMode");
    ioOut << m_safeMode;
}
//%outOfLineFunctions } /Xh6R7toYIiT+2Th1lxRRA
