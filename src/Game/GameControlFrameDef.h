//%includeGuardStart {
#ifndef GAMECONTROLFRAMEDEF_H
#define GAMECONTROLFRAMEDEF_H
//%includeGuardStart } swp/Jc+nKOw2Clebi7fIBA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameControlFrameDef.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9BjTYy5ecWwzm5Ki2KMqog
/*
 * $Id: GameControlFrameDef.h,v 1.8 2004/01/02 21:13:06 southa Exp $
 * $Log: GameControlFrameDef.h,v $
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
    bool LeftPressed(void) const { return keyState & (1<<0); }
    bool RightPressed(void) const { return keyState & (1<<1); }
    bool UpPressed(void) const { return keyState & (1<<2); }
    bool DownPressed(void) const { return keyState & (1<<3); }
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
