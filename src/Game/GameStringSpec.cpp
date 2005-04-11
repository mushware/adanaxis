//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameStringSpec.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ep1od/J3YQ7pEkqyBR5wLw
/*
 * $Id$
 * $Log$
 */

#include "GameStringSpec.h"

//%outOfLineFunctions {

const char *GameStringSpec::AutoNameGet(void) const
{
    return "GameStringSpec";
}

MushcoreVirtualObject *GameStringSpec::AutoClone(void) const
{
    return new GameStringSpec(*this);
}

MushcoreVirtualObject *GameStringSpec::AutoCreate(void) const
{
    return new GameStringSpec;
}

MushcoreVirtualObject *GameStringSpec::AutoVirtualFactory(void)
{
    return new GameStringSpec;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameStringSpec", GameStringSpec::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameStringSpec::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "string=" << m_string << ", ";
    ioOut << "posicity=" << m_posicity << ", ";
    ioOut << "startColour=" << m_startColour << ", ";
    ioOut << "midColour=" << m_midColour << ", ";
    ioOut << "endColour=" << m_endColour << ", ";
    ioOut << "startTime=" << m_startTime << ", ";
    ioOut << "endTime=" << m_endTime << ", ";
    ioOut << "fadeTime=" << m_fadeTime << ", ";
    ioOut << "startSize=" << m_startSize << ", ";
    ioOut << "midSize=" << m_midSize << ", ";
    ioOut << "endSize=" << m_endSize;
    ioOut << "]";
}
bool
GameStringSpec::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "string")
    {
        ioIn >> m_string;
    }
    else if (inTagStr == "posicity")
    {
        ioIn >> m_posicity;
    }
    else if (inTagStr == "startColour")
    {
        ioIn >> m_startColour;
    }
    else if (inTagStr == "midColour")
    {
        ioIn >> m_midColour;
    }
    else if (inTagStr == "endColour")
    {
        ioIn >> m_endColour;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> m_startTime;
    }
    else if (inTagStr == "endTime")
    {
        ioIn >> m_endTime;
    }
    else if (inTagStr == "fadeTime")
    {
        ioIn >> m_fadeTime;
    }
    else if (inTagStr == "startSize")
    {
        ioIn >> m_startSize;
    }
    else if (inTagStr == "midSize")
    {
        ioIn >> m_midSize;
    }
    else if (inTagStr == "endSize")
    {
        ioIn >> m_endSize;
    }
    else
    {
        return false;
    }
    return true;
}
void
GameStringSpec::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("string");
    ioOut << m_string;
    ioOut.TagSet("posicity");
    ioOut << m_posicity;
    ioOut.TagSet("startColour");
    ioOut << m_startColour;
    ioOut.TagSet("midColour");
    ioOut << m_midColour;
    ioOut.TagSet("endColour");
    ioOut << m_endColour;
    ioOut.TagSet("startTime");
    ioOut << m_startTime;
    ioOut.TagSet("endTime");
    ioOut << m_endTime;
    ioOut.TagSet("fadeTime");
    ioOut << m_fadeTime;
    ioOut.TagSet("startSize");
    ioOut << m_startSize;
    ioOut.TagSet("midSize");
    ioOut << m_midSize;
    ioOut.TagSet("endSize");
    ioOut << m_endSize;
}
//%outOfLineFunctions } sblV3eFjDnx5MPJKPpstWg