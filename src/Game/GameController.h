#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameController.h,v 1.11 2002/12/20 13:17:38 southa Exp $
 * $Log: GameController.h,v $
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

#include "Mushcore.h"
#include "mushGL.h"

class GameControlFrameDef;

class GameController
{
public:
    GameController();
    void StateGet(GameControlFrameDef& outDef, Mushware::U32 inAtMsec);

private:
    std::vector<GLKeys::tKeyValue> m_keysOfInterest;
    std::vector<bool> m_keyState;
    Mushware::tVal m_lastMouseX;
    Mushware::tVal m_lastMouseY;
    Mushware::S32 m_lastUnboundedMouseX;
    Mushware::S32 m_lastUnboundedMouseY;
    bool m_lastMouseValid;
};
#endif
