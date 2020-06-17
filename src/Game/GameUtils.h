//%includeGuardStart {
#ifndef GAMEUTILS_H
#define GAMEUTILS_H
//%includeGuardStart } tnIW58cbpoexh5GV89K1gQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } SIoK49BCJNVx5E6z9FQxwQ
/*
 * $Id: GameUtils.h,v 1.6 2007/04/18 09:22:16 southa Exp $
 * $Log: GameUtils.h,v $
 * Revision 1.6  2007/04/18 09:22:16  southa
 * Header and level fixes
 *
 * Revision 1.5  2006/06/01 15:39:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
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
    static Mushware::U32 HashGenerate(Mushware::U32 inCode);
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
