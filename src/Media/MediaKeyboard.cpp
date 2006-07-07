//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaKeyboard.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 7mgogG6D/5MIAEtL8RcBUQ
/*
 * $Id$
 * $Log$
 */

#include "MediaKeyboard.h"

#include "MediaSDL.h"

using namespace Mushware;
using namespace std;

const char *
MediaKeyboard::KeySymbolToName(Mushware::U32 keyValue)
{
    return SDL_GetKeyName(static_cast<SDLKey>(keyValue));
}
