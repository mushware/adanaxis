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
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lqBeDRNm3b3SMSEVf+F/iQ
/*
 * $Id: MeshMoverAppHandler.h,v 1.2 2004/01/02 21:13:10 southa Exp $
 * $Log: MeshMoverAppHandler.h,v $
 * Revision 1.2  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "mushMushcore.h"
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
