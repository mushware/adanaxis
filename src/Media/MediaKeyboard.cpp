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
 * $Id: MediaKeyboard.cpp,v 1.2 2006/07/08 16:05:57 southa Exp $
 * $Log: MediaKeyboard.cpp,v $
 * Revision 1.2  2006/07/08 16:05:57  southa
 * Ruby menus and key handling
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MediaKeyboard.h"

#include "MediaSDL.h"

using namespace Mushware;
using namespace std;

const char *
MediaKeyboard::KeySymbolToName(Mushware::U32 keyValue)
{
    const char *retVal = "unknown";

    if (keyValue < kKey_LAST)
    {
        retVal = SDL_GetKeyName(static_cast<SDLKey>(keyValue));
    }
    else
    {
        switch (keyValue)
        {
            case kKeyMouse0:
                retVal = "mouse0";
                break;
                
            case kKeyMouse1:
                retVal = "mouse1";
                break;
                
            case kKeyMouse2:
                retVal = "mouse2";
                break;
                
            case kKeyMouse3:
                retVal = "mouse3";
                break;
                
            case kKeyMouse4:
                retVal = "mouse4";
                break;

            default:
                // Leave as unknown
                break;
        }
    }
    return retVal;
}
