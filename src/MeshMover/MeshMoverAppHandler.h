//%includeGuardStart {
#ifndef MESHMOVERAPPHANDLER_H
#define MESHMOVERAPPHANDLER_H
//%includeGuardStart } IY/3JnxHgqkhATuA1G5YCg
//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverAppHandler.h
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
//%Header } 0Y+hkNZkIzRHSIzlaMRh3g
/*
 * $Id: MeshMoverAppHandler.h,v 1.5 2006/06/01 15:39:14 southa Exp $
 * $Log: MeshMoverAppHandler.h,v $
 * Revision 1.5  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
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
