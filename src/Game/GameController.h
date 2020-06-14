//%includeGuardStart {
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
//%includeGuardStart } s4KiuDKiwe3wHmCtED9rjA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameController.h
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
//%Header } s8d8IpRvPNZL6ViCPMax7g
/*
 * $Id: GameController.h,v 1.19 2006/07/08 16:05:56 southa Exp $
 * $Log: GameController.h,v $
 * Revision 1.19  2006/07/08 16:05:56  southa
 * Ruby menus and key handling
 *
 * Revision 1.18  2006/06/01 15:38:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.16  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.15  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.14  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:37  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.11  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.9  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.8  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.5  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.1  2002/06/05 15:53:25  southa
 * Player and keyboard control
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

class GameControlFrameDef;

class GameController
{
public:
    GameController();
    void StateGet(GameControlFrameDef& outDef, Mushware::U32 inAtMsec);

private:
    std::vector<Mushware::S32> m_keysOfInterest;
    std::vector<bool> m_keyState;
    Mushware::tVal m_lastMouseX;
    Mushware::tVal m_lastMouseY;
    Mushware::S32 m_lastUnboundedMouseX;
    Mushware::S32 m_lastUnboundedMouseY;
    bool m_lastMouseValid;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
