//%includeGuardStart {
#ifndef GAMECONTROLFRAMEDEF_H
#define GAMECONTROLFRAMEDEF_H
//%includeGuardStart } swp/Jc+nKOw2Clebi7fIBA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameControlFrameDef.h
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
//%Header } qO2tD6AH61KWDKiC/hhTFQ
/*
 * $Id: GameControlFrameDef.h,v 1.12 2006/06/01 15:38:57 southa Exp $
 * $Log: GameControlFrameDef.h,v $
 * Revision 1.12  2006/06/01 15:38:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.10  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.9  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.8  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:37  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.4  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.2  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.1  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 */

#include "mushMushcore.h"

class GameControlFrameDef
{
public:
    bool LeftPressed(void) const { return (keyState & (1<<0)) != 0; }
    bool RightPressed(void) const { return (keyState & (1<<1)) != 0; }
    bool UpPressed(void) const { return (keyState & (1<<2)) != 0; }
    bool DownPressed(void) const { return (keyState & (1<<3)) != 0; }
    void Print(std::ostream& ioOut) const;
    
    Mushware::S8 mouseDeltaX;
    Mushware::S8 mouseDeltaY;
    Mushware::U8 keyState;
};

inline std::ostream&
operator<<(std::ostream& ioOut, const GameControlFrameDef& inDef)
{
    inDef.Print(ioOut);
    return ioOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
