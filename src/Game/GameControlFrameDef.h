/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameControlFrameDef
{
public:
    bool LeftPressed(void) const { return keyState & (1<<0); }
    bool RightPressed(void) const { return keyState & (1<<1); }
    bool UpPressed(void) const { return keyState & (1<<2); }
    bool DownPressed(void) const { return keyState & (1<<3); }

    S8 mouseDeltaX;
    S8 mouseDeltaY;
    U8 keyState;
};
