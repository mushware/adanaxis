//%includeGuardStart {
#ifndef GAMEUTILS_H
#define GAMEUTILS_H
//%includeGuardStart } tnIW58cbpoexh5GV89K1gQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.h
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
//%Header } k666Ocml91vNr4/FqWJtSA
/*
 * $Id: GameUtils.h,v 1.3 2005/05/19 13:02:03 southa Exp $
 * $Log: GameUtils.h,v $
 * Revision 1.3  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.2  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.1  2005/04/10 00:10:40  southa
 * Registration
 *
 */

#include "mushMushcore.h"

#include "GameAppHandler.h"

class GameUtils
{
public:
    static Mushware::U32 Rotate(Mushware::U32 inVal, Mushware::U32 inRot);
    static Mushware::U32 GameUtils::HashGenerate(Mushware::U32 inCode);
    static bool CodeVerify(const std::string& inCode);
    static GameAppHandler *AppHandlerPtr(void);
    static GameAppHandler& AppHandler(void);
};

inline GameAppHandler *
GameUtils::AppHandlerPtr(void)
{
    GameAppHandler *pGameAppHandler=dynamic_cast<GameAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pGameAppHandler == NULL)
    {
        throw MushcoreLogicFail("Access to NULL GameApphandler");
    }
    return pGameAppHandler;
}

inline GameAppHandler&
GameUtils::AppHandler(void)
{
    return *AppHandlerPtr();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
