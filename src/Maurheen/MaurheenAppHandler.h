//%includeGuardStart {
#ifndef MAURHEENAPPHANDLER_H
#define MAURHEENAPPHANDLER_H
//%includeGuardStart } HgK1zer4UZTR54Q3rkXF4Q
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenAppHandler.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } Z2v8AMZEDS2eHAUcy+YvyQ
/*
 * $Id: MaurheenAppHandler.h,v 1.3 2006/06/01 15:39:11 southa Exp $
 * $Log: MaurheenAppHandler.h,v $
 * Revision 1.3  2006/06/01 15:39:11  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
 */

#include "mushMushcore.h"
#include "mushGame.h"

class MaurheenAppHandler : public GameAppHandler
{
public:
    MaurheenAppHandler();
    virtual ~MaurheenAppHandler();
    virtual void GameModeEnter(bool inResume);
    virtual void CurrentGameEnd(void);

protected:
    virtual void PrepareNewGame(void);

private:
    MushcoreDataRef<GameBase> m_gameRef;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
