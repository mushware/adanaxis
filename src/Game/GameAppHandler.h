#ifndef GAMEAPPHANDLER_H
#define GAMEAPPHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GameAppHandler.h,v 1.6 2002/06/27 12:36:06 southa Exp $
 * $Log: GameAppHandler.h,v $
 * Revision 1.6  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.4  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.3  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameBase;

class GameAppHandler : public SDLAppHandler
{
public:
    GameAppHandler(): m_pGame(NULL) {}
    virtual void Initialise(void);
    virtual void Display(void);
    virtual void Idle(void);

protected:
private:
    GameBase *m_pGame;
};
#endif
