//%includeGuardStart {
#ifndef GAMEBASE_H
#define GAMEBASE_H
//%includeGuardStart } fJfmVcVY6Dz2kLgb11HrMw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameBase.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } pHPV/SGbTI7tNUadYLuaGw
/*
 * $Id: GameBase.h,v 1.25 2006/06/01 15:38:56 southa Exp $
 * $Log: GameBase.h,v $
 * Revision 1.25  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.24  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.23  2004/03/06 13:59:59  southa
 * Fixes
 *
 * Revision 1.22  2004/03/06 13:13:42  southa
 * Maurheen created
 *
 * Revision 1.21  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.20  2004/01/02 21:13:06  southa
 * Source conditioning
 *
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

#include "mushMushcore.h"

class GameAppHandler;

class GameBase : public MushcoreVirtualObject
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
