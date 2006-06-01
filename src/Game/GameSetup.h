//%includeGuardStart {
#ifndef GAMESETUP_H
#define GAMESETUP_H
//%includeGuardStart } WY8ETZV6ZIrY2yqsFnXy7g
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSetup.h
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
//%Header } wghvR7XY7ttGX+TY0ahFfA
/*
 * $Id: GameSetup.h,v 1.20 2005/06/20 14:30:34 southa Exp $
 * $Log: GameSetup.h,v $
 * Revision 1.20  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.19  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.18  2005/02/10 12:33:59  southa
 * Template fixes
 *
 * Revision 1.17  2004/03/06 13:59:59  southa
 * Fixes
 *
 * Revision 1.16  2004/03/06 13:13:42  southa
 * Maurheen created
 *
 * Revision 1.15  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.14  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:54  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/03/10 21:57:11  southa
 * ic2 revisions
 *
 * Revision 1.10  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.9  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/05 23:52:52  southa
 * Network management and status
 *
 * Revision 1.6  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.5  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.4  2002/11/28 15:51:21  southa
 * Kill image defs as well
 *
 * Revision 1.3  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.2  2002/11/16 12:43:23  southa
 * GameApp mode switching
 *
 * Revision 1.1  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 */

#include "mushMushcore.h"

#include "GameBase.h"

//:generate virtual standard ostream xml1 
class GameSetup : public GameBase
{
public:
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateConfigInit,
        kGameStateConfig
    };
    
    GameSetup();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);

protected:
    void ConfigInit(void);
    void Config(void);
    void Ticker(void);
    void KeyControl(void);

    static bool MustlPermissionFunction(const std::string& inAddress);
    
private:
    enum
    {
        kSlowSleepMsec=10,
        kFastSleepMsec=1,
        kTickerMsec=100
    };

    tGameState m_gameState;
    std::string m_configURL;
    Mushware::U32 m_currentMsec;
    Mushware::U32 m_lastTickerMsec;
    bool m_windowClicked;
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
operator<<(std::ostream& ioOut, const GameSetup& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Kk07ttNWtpNW/5FfY53DHQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
