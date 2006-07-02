//%includeGuardStart {
#ifndef ADANAXISGAME_H
#define ADANAXISGAME_H
//%includeGuardStart } bEcHxZFuCUNIC6khESaNzA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wOXl6eoMycMTXcUsBJ4Pgg
/*
 * $Id: AdanaxisGame.h,v 1.14 2006/06/30 15:05:31 southa Exp $
 * $Log: AdanaxisGame.h,v $
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
    
    virtual void UpdateFromConfig(void);
    
    static void Install(void);
    
protected:
    virtual void LocalGameCreate(MushGameAppHandler& inAppHandler);
        
private:
    AdanaxisSaveData& SaveData();
    AdanaxisVolatileData& VolatileData();
    AdanaxisLogic& Logic();
    
    bool m_inited; //:ignore
    std::string m_name;
    
    Mushware::tMsec m_modeKeypressMsec;
    Mushware::U32 m_newMode;
    
    MushcoreDataRef<MushGameSaveData> m_saveDataRef;
    MushcoreDataRef<MushGameVolatileData> m_volatileDataRef;
    MushcoreDataRef<MushGameClient> m_clientRef;
    MushcoreDataRef<MushGameServer> m_serverRef;
    MushcoreDataRef<MushGameLogic> m_logicRef;
    
    AdanaxisConfig m_config;
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};

inline AdanaxisSaveData&
AdanaxisGame::SaveData()
{
    AdanaxisSaveData *pSaveData = dynamic_cast<AdanaxisSaveData *>(&m_saveDataRef.WRef());
    if (pSaveData == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisSaveData of wrong type '")+m_saveDataRef.Ref().AutoName()+"'");
    }
    return *pSaveData;
}

inline AdanaxisVolatileData&
AdanaxisGame::VolatileData()
{
    AdanaxisVolatileData *pVolatileData = dynamic_cast<AdanaxisVolatileData *>(&m_volatileDataRef.WRef());
    if (pVolatileData == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisVolatileData of wrong type '")+m_volatileDataRef.Ref().AutoName()+"'");
    }
    return *pVolatileData;
}

inline AdanaxisLogic&
AdanaxisGame::Logic()
{
    AdanaxisLogic *pLogic = dynamic_cast<AdanaxisLogic *>(&m_logicRef.WRef());
    if (pLogic == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisLogic of wrong type '")+m_logicRef.Ref().AutoName()+"'");
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
