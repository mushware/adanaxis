//%includeGuardStart {
#ifndef GAMECONTROLFRAMEDEF_H
#define GAMECONTROLFRAMEDEF_H
//%includeGuardStart } swp/Jc+nKOw2Clebi7fIBA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameControlFrameDef.h
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
//%Header } U2n95q3NjBQJ2aa4LTLEFw
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
