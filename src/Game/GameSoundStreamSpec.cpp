//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundStreamSpec.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } qcCaIX9JlAQg882Z3nNceg
/*
 * $Id$
 * $Log$
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
