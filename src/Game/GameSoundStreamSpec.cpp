//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundStreamSpec.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } PEy2CHiJNmS7LfNQy1wt/g
/*
 * $Id: GameSoundStreamSpec.cpp,v 1.1 2005/03/25 19:13:49 southa Exp $
 * $Log: GameSoundStreamSpec.cpp,v $
 * Revision 1.1  2005/03/25 19:13:49  southa
 * GameDialogue work
 *
 */

#include "GameSoundStreamSpec.h"

//%outOfLineFunctions {

const char *GameSoundStreamSpec::AutoNameGet(void) const
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
        ioIn >> *this;
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
//%outOfLineFunctions } nNfWfv+1RoZRt457C5NYyQ
