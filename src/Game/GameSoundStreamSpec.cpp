//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundStreamSpec.cpp
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
//%Header } pDWmIPx5iekbb390UvlcEA
/*
 * $Id: GameSoundStreamSpec.cpp,v 1.6 2006/06/01 15:39:00 southa Exp $
 * $Log: GameSoundStreamSpec.cpp,v $
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

#include "GameSoundStreamSpec.h"

//%outOfLineFunctions {

const char *GameSoundStreamSpec::AutoName(void) const
{
    return "GameSoundStreamSpec";
}

MushcoreVirtualObject *GameSoundStreamSpec::AutoClone(void) const
{
    return new GameSoundStreamSpec(*this);
}

MushcoreVirtualObject *GameSoundStreamSpec::AutoCreate(void) const
{
    return new GameSoundStreamSpec;
}

MushcoreVirtualObject *GameSoundStreamSpec::AutoVirtualFactory(void)
{
    return new GameSoundStreamSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameSoundStreamSpec", GameSoundStreamSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameSoundStreamSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "soundStreamRef=" << m_soundStreamRef << ", ";
    ioOut << "loop=" << loop << ", ";
    ioOut << "startTime=" << startTime;
    ioOut << "]";
}
bool
GameSoundStreamSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "soundStreamRef")
    {
        ioIn >> m_soundStreamRef;
    }
    else if (inTagStr == "loop")
    {
        ioIn >> loop;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> startTime;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GameSoundStreamSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("soundStreamRef");
    ioOut << m_soundStreamRef;
    ioOut.TagSet("loop");
    ioOut << loop;
    ioOut.TagSet("startTime");
    ioOut << startTime;
}
//%outOfLineFunctions } VgPbUQN9b8XsIxfXD40Jsw
