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
 * $Id: GameControlFrameDef.cpp,v 1.5 2003/01/13 14:31:57 southa Exp $
 * $Log: GameControlFrameDef.cpp,v $
 * Revision 1.5  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.4  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.1  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 */

#include "GameControlFrameDef.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
GameControlFrameDef::Print(ostream& ioOut) const
{
    ioOut << "mouseDeltaX=" << static_cast<S32>(mouseDeltaX);
    ioOut << ", mouseDeltaY=" << static_cast<S32>(mouseDeltaY);
    ioOut << ", keyState=" << hex << static_cast<U32>(keyState) << dec;
}
