#ifndef GAMECONTROLFRAMEDEF_H
#define GAMECONTROLFRAMEDEF_H
/*
 * $Id: GameControlFrameDef.h,v 1.2 2002/12/04 12:54:41 southa Exp $
 * $Log: GameControlFrameDef.h,v $
 * Revision 1.2  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.1  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 */

#include "mushCore.h"

class GameControlFrameDef
{
public:
    bool LeftPressed(void) const { return keyState & (1<<0); }
    bool RightPressed(void) const { return keyState & (1<<1); }
    bool UpPressed(void) const { return keyState & (1<<2); }
    bool DownPressed(void) const { return keyState & (1<<3); }
    void Print(ostream& ioOut) const;
    
    S8 mouseDeltaX;
    S8 mouseDeltaY;
    U8 keyState;
};

inline ostream&
operator<<(ostream& ioOut, const GameControlFrameDef& inDef)
{
    inDef.Print(ioOut);
    return ioOut;
}
#endif
