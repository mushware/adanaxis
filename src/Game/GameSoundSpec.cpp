//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundSpec.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /0ZdV5pg3LCM+mFc6x5hnQ
/*
 * $Id$
 * $Log$
 */

#include "GameSoundSpec.h"

//%outOfLineFunctions {

const char *GameSoundSpec::AutoNameGet(void) const
{
    return "GameSoundSpec";
}

MushcoreVirtualObject *GameSoundSpec::AutoClone(void) const
{
    return new GameSoundSpec(*this);
}

MushcoreVirtualObject *GameSoundSpec::AutoCreate(void) const
{
    return new GameSoundSpec;
}

MushcoreVirtualObject *GameSoundSpec::AutoVirtualFactory(void)
{
    return new GameSoundSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameSoundSpec", GameSoundSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameSoundSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "soundRef=" << m_soundRef << ", ";
    ioOut << "startTime=" << m_startTime;
    ioOut << "]";
}
bool
GameSoundSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "soundRef")
    {
        ioIn >> m_soundRef;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> m_startTime;
    }
    else
    {
        return false;
    }
    return true;
}
void
GameSoundSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("soundRef");
    ioOut << m_soundRef;
    ioOut.TagSet("startTime");
    ioOut << m_startTime;
}
//%outOfLineFunctions } i7d7xiATDfSFzlwd6RWIYg
