//%includeGuardStart {
#ifndef MAURHEENAPPHANDLER_H
#define MAURHEENAPPHANDLER_H
//%includeGuardStart } HgK1zer4UZTR54Q3rkXF4Q
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenAppHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } dVunOvDjIjn4VIq6AqCPMA
/*
 * $Id: MaurheenAppHandler.h,v 1.3 2004/01/06 20:46:51 southa Exp $
 * $Log: MaurheenAppHandler.h,v $
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
