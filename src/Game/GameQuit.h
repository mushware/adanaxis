//%includeGuardStart {
#ifndef GAMEQUIT_H
#define GAMEQUIT_H
//%includeGuardStart } PBBuTT3bIKf/ZxJFSt1W9w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameQuit.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vWBeosVH87okVVejo5ZQ8Q
/*
 * $Id: GameQuit.h,v 1.10 2004/03/06 13:13:42 southa Exp $
 * $Log: GameQuit.h,v $
 * Revision 1.10  2004/03/06 13:13:42  southa
 * Maurheen created
 *
 * Revision 1.9  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.8  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:52  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.4  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.1  2002/11/18 18:55:58  southa
 * Game resume and quit
 *
 */

#include "mushMushcore.h"

#include "GameBase.h"

//:generate standard ostream xml1
class GameQuit : public GameBase
{
public:
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateInit,
        kGameStateTiming
    };

    GameQuit();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);

protected:
    
private:
    void Init(void);
    void Timing(void);

    enum
    {
        kQuitHangTime=500, // msec to hang around regardless
        kQuitTimeout=5000  // msec to wait for web links
    };

    tGameState m_gameState;
    Mushware::U32 m_startMsec;
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual GameQuit *AutoClone(void) const;
    virtual GameQuit *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } rXybxo5CBx52i/GTLBAzYw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GameQuit& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } m+yKhbiWkoR/Rp6PBe02HQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
