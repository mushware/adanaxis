/*
 * $Id: GameControlFrameDef.cpp,v 1.1 2002/12/04 00:37:11 southa Exp $
 * $Log: GameControlFrameDef.cpp,v $
 * Revision 1.1  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 */

#include "GameControlFrameDef.h"

void
GameControlFrameDef::Print(ostream& ioOut) const
{
    ioOut << "mouseDeltaX=" << static_cast<S32>(mouseDeltaX);
    ioOut << ", mouseDeltaY=" << static_cast<S32>(mouseDeltaY);
    ioOut << ", keyState=" << hex << static_cast<U32>(keyState) << dec;
}
