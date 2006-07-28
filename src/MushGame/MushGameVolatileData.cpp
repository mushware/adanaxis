//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameVolatileData.cpp
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
//%Header } mGoZWUiZsKFfWNio1FcVLw
/*
 * $Id: MushGameVolatileData.cpp,v 1.9 2006/07/20 12:22:22 southa Exp $
 * $Log: MushGameVolatileData.cpp,v $
 * Revision 1.9  2006/07/20 12:22:22  southa
 * Precache display
 *
 * Revision 1.8  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.7  2006/07/04 16:55:28  southa
 * Ruby key handling
 *
 * Revision 1.6  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.4  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:52  southa
 * MushGame work
 *
 */

#include "MushGameVolatileData.h"

MUSHCORE_DATA_INSTANCE(MushGameVolatileData);

MushGameVolatileData::MushGameVolatileData() :
    m_playerUplinkPeriodMsec(1000),
    m_lastPlayerUplinkMsec(0),
    m_quickPlayerUplinkRequired(false),
    m_gameMsec(0),
    m_lastGameMsec(0),
    m_frameMsec(0),
    m_rubyGame(Mushware::kRubyQnil),
    m_gameMode(kGameModeMenu),
    m_preCache(false),
    m_isMenuBackdrop(false)
{
}

//%outOfLineFunctions {

const char *MushGameVolatileData::AutoName(void) const
{
    return "MushGameVolatileData";
}

MushcoreVirtualObject *MushGameVolatileData::AutoClone(void) const
{
    return new MushGameVolatileData(*this);
}

MushcoreVirtualObject *MushGameVolatileData::AutoCreate(void) const
{
    return new MushGameVolatileData;
}

MushcoreVirtualObject *MushGameVolatileData::AutoVirtualFactory(void)
{
    return new MushGameVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameVolatileData", MushGameVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "playerUplinkPeriodMsec=" << m_playerUplinkPeriodMsec << ", ";
    ioOut << "lastPlayerUplinkMsec=" << m_lastPlayerUplinkMsec << ", ";
    ioOut << "quickPlayerUplinkRequired=" << m_quickPlayerUplinkRequired << ", ";
    ioOut << "gameMsec=" << m_gameMsec << ", ";
    ioOut << "lastGameMsec=" << m_lastGameMsec << ", ";
    ioOut << "frameMsec=" << m_frameMsec << ", ";
    ioOut << "rubyGame=" << m_rubyGame << ", ";
    ioOut << "gameMode=" << m_gameMode << ", ";
    ioOut << "preCache=" << m_preCache << ", ";
    ioOut << "isMenuBackdrop=" << m_isMenuBackdrop;
    ioOut << "]";
}
bool
MushGameVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerUplinkPeriodMsec")
    {
        ioIn >> m_playerUplinkPeriodMsec;
    }
    else if (inTagStr == "lastPlayerUplinkMsec")
    {
        ioIn >> m_lastPlayerUplinkMsec;
    }
    else if (inTagStr == "quickPlayerUplinkRequired")
    {
        ioIn >> m_quickPlayerUplinkRequired;
    }
    else if (inTagStr == "gameMsec")
    {
        ioIn >> m_gameMsec;
    }
    else if (inTagStr == "lastGameMsec")
    {
        ioIn >> m_lastGameMsec;
    }
    else if (inTagStr == "frameMsec")
    {
        ioIn >> m_frameMsec;
    }
    else if (inTagStr == "rubyGame")
    {
        ioIn >> m_rubyGame;
    }
    else if (inTagStr == "gameMode")
    {
        ioIn >> m_gameMode;
    }
    else if (inTagStr == "preCache")
    {
        ioIn >> m_preCache;
    }
    else if (inTagStr == "isMenuBackdrop")
    {
        ioIn >> m_isMenuBackdrop;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("playerUplinkPeriodMsec");
    ioOut << m_playerUplinkPeriodMsec;
    ioOut.TagSet("lastPlayerUplinkMsec");
    ioOut << m_lastPlayerUplinkMsec;
    ioOut.TagSet("quickPlayerUplinkRequired");
    ioOut << m_quickPlayerUplinkRequired;
    ioOut.TagSet("gameMsec");
    ioOut << m_gameMsec;
    ioOut.TagSet("lastGameMsec");
    ioOut << m_lastGameMsec;
    ioOut.TagSet("frameMsec");
    ioOut << m_frameMsec;
    ioOut.TagSet("rubyGame");
    ioOut << m_rubyGame;
    ioOut.TagSet("gameMode");
    ioOut << m_gameMode;
    ioOut.TagSet("preCache");
    ioOut << m_preCache;
    ioOut.TagSet("isMenuBackdrop");
    ioOut << m_isMenuBackdrop;
}
//%outOfLineFunctions } XQ3PP6Tp7uSWdgyzoypTcg
