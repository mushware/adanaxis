//%includeGuardStart {
#ifndef GAMEBASE_H
#define GAMEBASE_H
//%includeGuardStart } fJfmVcVY6Dz2kLgb11HrMw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameBase.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } er0793/i2x5C77SKjyr/Ag
/*
 * $Id: GameBase.h,v 1.19 2003/10/04 12:22:59 southa Exp $
 * $Log: GameBase.h,v $
 * Revision 1.19  2003/10/04 12:22:59  southa
 * File renaming
 *
 * Revision 1.18  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.17  2003/08/21 23:08:34  southa
 * Fixed file headers
 *
 * Revision 1.16  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.15  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
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
 * Pickleable InfernalContract
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

#include "Mushcore.h"

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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
