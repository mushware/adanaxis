//%includeGuardStart {
#ifndef ADANAXISAPPHANDLER_H
#define ADANAXISAPPHANDLER_H
//%includeGuardStart } v8t9CZvWGMEKr8skTuEKcQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.h
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
//%Header } K3hFA55rGfb+D50+6fnrZg
/*
 * $Id: AdanaxisAppHandler.h,v 1.2 2005/06/14 13:25:32 southa Exp $
 * $Log: AdanaxisAppHandler.h,v $
 * Revision 1.2  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

class AdanaxisAppHandler : public MushGameAppHandler
{
public:
    AdanaxisAppHandler(const std::string& inName = "");
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
