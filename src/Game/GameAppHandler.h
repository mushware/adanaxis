/*
 * $Id: GameAppHandler.h,v 1.4 2002/06/20 15:50:30 southa Exp $
 * $Log: GameAppHandler.h,v $
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
