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
 * $Id: MushGameVolatileData.cpp,v 1.13 2006/12/14 00:33:49 southa Exp $
 * $Log: MushGameVolatileData.cpp,v $
 * Revision 1.13  2006/12/14 00:33:49  southa
 * Control fix and audio pacing
 *
 * Revision 1.12  2006/11/21 10:08:24  southa
 * Initial cut scene handling
 *
 * Revision 1.11  2006/11/08 11:35:00  southa
 * Basic frame rate independence
 *
 * Revision 1.10  2006/07/28 11:14:29  southa
 * Records for multiple spaces
 *
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
    m_rubyLogic(Mushware::kRubyQnil),
    m_gameMode(kGameModeMenu),
    m_preCache(false),
    m_isMenuBackdrop(false),
    m_averageMsecPerFrame(1000.0/60.0),
    m_movesThisFrame(1)
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
    ioOut << "rubyLogic=" << m_rubyLogic << ", ";
    ioOut << "gameMode=" << m_gameMode << ", ";
    ioOut << "preCache=" << m_preCache << ", ";
    ioOut << "isMenuBackdrop=" << m_isMenuBackdrop << ", ";
    ioOut << "averageMsecPerFrame=" << m_averageMsecPerFrame << ", ";
    ioOut << "movesThisFrame=" << m_movesThisFrame << ", ";
    ioOut << "cutSceneNum=" << m_cutSceneNum << ", ";
    ioOut << "last100msTickMsec=" << m_last100msTickMsec;
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
    else if (inTagStr == "rubyLogic")
    {
        ioIn >> m_rubyLogic;
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
    else if (inTagStr == "averageMsecPerFrame")
    {
        ioIn >> m_averageMsecPerFrame;
    }
    else if (inTagStr == "movesThisFrame")
    {
        ioIn >> m_movesThisFrame;
    }
    else if (inTagStr == "cutSceneNum")
    {
        ioIn >> m_cutSceneNum;
    }
    else if (inTagStr == "last100msTickMsec")
    {
        ioIn >> m_last100msTickMsec;
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
    ioOut.TagSet("rubyLogic");
    ioOut << m_rubyLogic;
    ioOut.TagSet("gameMode");
    ioOut << m_gameMode;
    ioOut.TagSet("preCache");
    ioOut << m_preCache;
    ioOut.TagSet("isMenuBackdrop");
    ioOut << m_isMenuBackdrop;
    ioOut.TagSet("averageMsecPerFrame");
    ioOut << m_averageMsecPerFrame;
    ioOut.TagSet("movesThisFrame");
    ioOut << m_movesThisFrame;
    ioOut.TagSet("cutSceneNum");
    ioOut << m_cutSceneNum;
    ioOut.TagSet("last100msTickMsec");
    ioOut << m_last100msTickMsec;
}
//%outOfLineFunctions } cW173fn4jFpwriKTrZtOng
