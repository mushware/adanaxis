//%includeGuardStart {
#ifndef MESHMOVERAPPHANDLER_H
#define MESHMOVERAPPHANDLER_H
//%includeGuardStart } IY/3JnxHgqkhATuA1G5YCg
//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverAppHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 7FQ3+j23tG2UiA47bOMeJA
/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"
#include "mushGame.h"

class MeshMoverAppHandler : public GameAppHandler
{
public:
    MeshMoverAppHandler();
    virtual ~MeshMoverAppHandler();
    virtual void GameModeEnter(bool inResume);
    virtual void CurrentGameEnd(void);

protected:
    virtual void PrepareNewGame(void);

private:
    GameBase *m_pGame;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
