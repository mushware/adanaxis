//%includeGuardStart {
#ifndef ADANAXISAPPHANDLER_H
#define ADANAXISAPPHANDLER_H
//%includeGuardStart } v8t9CZvWGMEKr8skTuEKcQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.h
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
//%Header } TKLe5TOvUyhHao7V53Mj9Q
/*
 * $Id: AdanaxisAppHandler.h,v 1.4 2005/06/03 13:36:44 southa Exp $
 * $Log: AdanaxisAppHandler.h,v $
 */

#include "mushMushcore.h"
#include "mushGame.h"

class AdanaxisAppHandler : public GameAppHandler
{
public:
    AdanaxisAppHandler();
    virtual ~AdanaxisAppHandler();
    virtual void SetupModeEnter(void);
    virtual void GameModeEnter(bool inResume);
    virtual void CurrentGameEnd(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
protected:
    virtual void PrepareNewGame(void);

private:
    MushcoreDataRef<GameBase> m_gameRef;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
