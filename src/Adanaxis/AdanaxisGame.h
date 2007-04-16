//%includeGuardStart {
#ifndef ADANAXISGAME_H
#define ADANAXISGAME_H
//%includeGuardStart } bEcHxZFuCUNIC6khESaNzA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.2, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Oev6ZpRx7HopJxrJ/76MzQ
/*
 * $Id: AdanaxisGame.h,v 1.27 2007/03/12 21:05:59 southa Exp $
 * $Log: AdanaxisGame.h,v $
 * Revision 1.27  2007/03/12 21:05:59  southa
 * Scanner symbols
 *
 * Revision 1.26  2007/03/09 19:50:11  southa
 * Resident textures
 *
 * Revision 1.25  2007/03/07 11:29:24  southa
 * Level permission
 *
 * Revision 1.24  2006/11/25 21:26:31  southa
 * Display mode definitions
 *
 * Revision 1.23  2006/08/01 17:21:23  southa
 * River demo
 *
 * Revision 1.22  2006/07/31 11:01:36  southa
 * Music and dialogues
 *
 * Revision 1.21  2006/07/28 16:52:19  southa
 * Options work
 *
 * Revision 1.20  2006/07/27 13:51:33  southa
 * Menu and control fixes
 *
 * Revision 1.19  2006/07/26 16:37:21  southa
 * Options menu
 *
 * Revision 1.18  2006/07/12 11:22:41  southa
 * Advanced control menu
 *
 * Revision 1.17  2006/07/11 19:49:03  southa
 * Control menu
 *
 * Revision 1.16  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.15  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 * Revision 1.14  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
 * Revision 1.13  2006/06/20 19:06:51  southa
 * Object creation
 *
 * Revision 1.12  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.10  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.9  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.8  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/06/23 11:58:27  southa
 * MushGame link work
 *
 * Revision 1.6  2005/06/21 15:57:46  southa
 * MushGame work
 *
 * Revision 1.5  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.3  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisConfig.h"
#include "AdanaxisLogic.h"
#include "AdanaxisSaveData.h"

#include "API/mushMushcore.h"
#include "API/mushGame.h"
#include "API/mushGL.h"
#include "API/mushMushGame.h"

//:generate virtual standard ostream xml1
class AdanaxisGame : public MushGameBase
{
public:
    explicit AdanaxisGame(const std::string& inName="anon-adanaxis");
    virtual ~AdanaxisGame();
    virtual void Process(MushGameAppHandler& inAppHandler);
    virtual void Display(MushGameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, MushGameAppHandler& inAppHandler) const;
    virtual void SwapIn(MushGameAppHandler& inAppHandler);
    virtual void SwapOut(MushGameAppHandler& inAppHandler);
    virtual void Init(MushGameAppHandler& inAppHandler);
    virtual void ControlsToDefaultSet(MushGameAppHandler& inHandler);
    virtual const GLModeDef& DisplayModeDef(void) const;
    virtual void PreviousModeDef(void);
    virtual void NextModeDef(void);
    virtual void BrightnessSet(Mushware::tVal inValue);
    
    virtual void UpdateFromConfig(void);
    virtual void UpdateToConfig(void);
    virtual void ConfigSave(void);
    virtual const MushGameConfigBase& Config(void) const { return m_config; }
    virtual MushGameConfigBase& ConfigWRef(void) { return m_config; }
    
    static void Install(void);
    
protected:
    virtual void LocalGameCreate(MushGameAppHandler& inAppHandler);
        
private:
    AdanaxisSaveData& SaveData();
    AdanaxisVolatileData& VolatileData();
    AdanaxisLogic& Logic();
    
    bool m_inited; //:ignore
    std::string m_name;

    AdanaxisConfig m_config;
    bool m_startDialogueShown; //:readwrite
    
//%classPrototypes {
public:
    const bool& StartDialogueShown(void) const { return m_startDialogueShown; }
    void StartDialogueShownSet(const bool& inValue) { m_startDialogueShown=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } SLrcN/4B/Ouc3cX+vsN2/A
};

inline AdanaxisSaveData&
AdanaxisGame::SaveData()
{
    AdanaxisSaveData *pSaveData = dynamic_cast<AdanaxisSaveData *>(&SaveDataRef().WRef());
    if (pSaveData == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisSaveData of wrong type '")+SaveDataRef().Ref().AutoName()+"'");
    }
    return *pSaveData;
}

inline AdanaxisVolatileData&
AdanaxisGame::VolatileData()
{
    AdanaxisVolatileData *pVolatileData = dynamic_cast<AdanaxisVolatileData *>(&VolatileDataRef().WRef());
    if (pVolatileData == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisVolatileData of wrong type '")+VolatileDataRef().Ref().AutoName()+"'");
    }
    return *pVolatileData;
}

inline AdanaxisLogic&
AdanaxisGame::Logic()
{
    AdanaxisLogic *pLogic = dynamic_cast<AdanaxisLogic *>(&LogicRef().WRef());
    if (pLogic == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisLogic of wrong type '")+LogicRef().Ref().AutoName()+"'");
    }
    return *pLogic;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisGame& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } oGT4NWOaVulvioksdDMsUQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
