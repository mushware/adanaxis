//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameStringSpec.cpp
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
//%Header } eNQnZ9mXkx+CLF7sLqnxHg
/*
 * $Id: GameStringSpec.cpp,v 1.5 2005/07/02 00:42:37 southa Exp $
 * $Log: GameStringSpec.cpp,v $
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

#include "GameStringSpec.h"

//%outOfLineFunctions {

const char *GameStringSpec::AutoName(void) const
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
    ioOut << "posticity=" << m_posticity << ", ";
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "string")
    {
        ioIn >> m_string;
    }
    else if (inTagStr == "posticity")
    {
        ioIn >> m_posticity;
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
    ioOut.TagSet("posticity");
    ioOut << m_posticity;
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
//%outOfLineFunctions } g0m0lp9+h741nIHXwP02gQ
