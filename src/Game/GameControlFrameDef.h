#ifndef GAMECONTROLFRAMEDEF_H
#define GAMECONTROLFRAMEDEF_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameControlFrameDef.h,v 1.5 2003/01/11 13:03:12 southa Exp $
 * $Log: GameControlFrameDef.h,v $
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

#include "Mushcore.h"

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
#endif
