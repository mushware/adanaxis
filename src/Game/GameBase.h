#ifndef GAMEBASE_H
#define GAMEBASE_H
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
 * $Id: GameBase.h,v 1.14 2002/12/20 13:17:37 southa Exp $
 * $Log: GameBase.h,v $
 * Revision 1.14  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.13  2002/12/03 20:28:15  southa
 * Network, player and control work
 *
 * Revision 1.12  2002/11/16 12:43:21  southa
 * GameApp mode switching
 *
 * Revision 1.11  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.10  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.5  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.4  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.3  2002/05/10 22:38:22  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushCore.h"

class GameAppHandler;

class GameBase
{
public:
    virtual ~GameBase() {}
    virtual void Process(GameAppHandler& inHandler) = 0;
    virtual void Display(GameAppHandler& inHandler) = 0;
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inHandler) const = 0;
    virtual void SwapIn(GameAppHandler& inHandler) = 0;
    virtual void SwapOut(GameAppHandler& inHandler) = 0;

private:

};
#endif
