//%includeGuardStart {
#ifndef ADANAXISGAME_H
#define ADANAXISGAME_H
//%includeGuardStart } bEcHxZFuCUNIC6khESaNzA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.h
 *
 * Copyright: Andy Southgate 2005
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
//%Header } TlcXhfM+VEvZ0twh8kZG0Q
/*
 * $Id: AdanaxisGame.h,v 1.6 2005/06/21 15:57:46 southa Exp $
 * $Log: AdanaxisGame.h,v $
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
#include "AdanaxisSaveData.h"

#include "API/mushMushcore.h"
#include "API/mushGame.h"
#include "API/mushGL.h"
#include "API/mushMushGame.h"

//:generate virtual standard ostream xml1
class AdanaxisGame : public GameBase
{
public:
    explicit AdanaxisGame(const std::string& inName="anon-adanaxis");
    virtual ~AdanaxisGame();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);
    virtual void Init(GameAppHandler& inAppHandler);
    
    static void Install(void);
    
protected:
    virtual void LocalGameCreate(GameAppHandler& inAppHandler);
        
private:
    AdanaxisSaveData& SaveData() { return dynamic_cast<AdanaxisSaveData&>(m_saveDataRef.WRef()); }
    MushGameLogic& Logic() { return dynamic_cast<MushGameLogic&>(m_logicRef.WRef()); }
    
    bool m_inited; //:ignore
    std::string m_name;
    
    Mushware::tVal m_modeKeypressMsec;
    Mushware::U32 m_newMode;
    
    MushcoreDataRef<MushGameSaveData> m_saveDataRef;
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
