//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameControlFrameDef.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Rii0N4GREYqBNZeGL0rglg
/*
 * $Id: GameControlFrameDef.cpp,v 1.7 2003/09/17 19:40:31 southa Exp $
 * $Log: GameControlFrameDef.cpp,v $
 * Revision 1.7  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:37  southa
 * Fixed file headers
 *
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
