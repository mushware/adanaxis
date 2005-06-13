//%includeGuardStart {
#ifndef ADANAXISGAME_H
#define ADANAXISGAME_H
//%includeGuardStart } bEcHxZFuCUNIC6khESaNzA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisGame.h
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
//%Header } E57ZiHI9MHqONqF4YIacTw
/*
 * $Id: AdanaxisGame.h,v 1.14 2005/05/19 13:02:22 southa Exp $
 * $Log: AdanaxisGame.h,v $
 */

#include "mushMushcore.h"
#include "mushGame.h"
#include "mushGL.h"

#include "AdanaxisConfig.h"

//:generate virtual standard ostream xml1
class AdanaxisGame : public GameBase
{
public:
    AdanaxisGame();
    virtual ~AdanaxisGame();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);
    virtual void Init(GameAppHandler& inAppHandler);
    
    static void Install(void);
    
protected:
    
private:

    bool m_inited; //:ignore
    Mushware::tVal m_modeKeypressMsec;
    Mushware::U32 m_newMode;
    
    MushcoreData<GameDialogue> m_dialogues;
    
    AdanaxisConfig m_config;
    
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FwEN8XJox/Ejr30NeyHzCg
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
