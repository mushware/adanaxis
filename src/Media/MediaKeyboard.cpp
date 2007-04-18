//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaKeyboard.cpp
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
//%Header } zUTLjSawWr0aOORTNWYzRQ
/*
 * $Id: MediaKeyboard.cpp,v 1.6 2006/11/08 18:30:54 southa Exp $
 * $Log: MediaKeyboard.cpp,v $
 * Revision 1.6  2006/11/08 18:30:54  southa
 * Key and axis configuration
 *
 * Revision 1.5  2006/07/11 19:49:04  southa
 * Control menu
 *
 * Revision 1.4  2006/07/11 12:37:52  southa
 * Control configuration
 *
 * Revision 1.3  2006/07/10 16:01:19  southa
 * Control menu work
 *
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

std::string
MediaKeyboard::KeySymbolToName(Mushware::U32 keyValue)
{
    std::string retVal = "unknown";

    if (keyValue < kKey_LAST)
    {
        retVal = SDL_GetKeyName(static_cast<SDLKey>(keyValue));
        if (retVal == "left ctrl") retVal = "l-ctrl";
        if (retVal == "right ctrl") retVal = "r-ctrl";
        if (retVal == "left") retVal = "left arrow";
        if (retVal == "right") retVal = "right arrow";
        if (retVal == "up") retVal = "up arrow";
        if (retVal == "down") retVal = "down arrow";
        if (retVal == "enter") retVal = "entr";
        if (retVal == "[0]") retVal = "kp0";
        if (retVal == "[1]") retVal = "kp1";
        if (retVal == "[2]") retVal = "kp2";
        if (retVal == "[3]") retVal = "kp3";
        if (retVal == "[4]") retVal = "kp4";
        if (retVal == "[5]") retVal = "kp5";
        if (retVal == "[6]") retVal = "kp6";
        if (retVal == "[7]") retVal = "kp7";
        if (retVal == "[8]") retVal = "kp8";
        if (retVal == "[9]") retVal = "kp9";
    }
    else if (keyValue >= kKeyMouse0 && keyValue <= kKeyMouse6)
    {
        switch (keyValue)
        {
            case kKeyMouse0:
#if defined(MACOSX) || defined(__APPLE__)
                retVal = "mouse click";
#else
                retVal = "mouse left";
#endif
                break;
                
            case kKeyMouse1:
                retVal = "mouse middle";
                break;
                
            case kKeyMouse2:
                retVal = "mouse right";
                break;
                
            case kKeyMouse3:
                retVal = "wheel up";
                break;
                
            case kKeyMouse4:
                retVal = "wheel down";
                break;
                
            case kKeyMouse5:
                retVal = "mouse 5";
                break;
                
            case kKeyMouse6:
                retVal = "mouse 6";
                break;
                
            default:
                // Leave as unknown
                break;
        }
    }
    else if (keyValue >= kKeyStick0 && keyValue <= kKeyStick5)
    {
        ostringstream nameStream;
        U32 base = (keyValue - kKeyStick0) / kKeyStickSpacing;
        U32 fromBase = (keyValue - kKeyStick0) % kKeyStickSpacing;
        if (fromBase < kKeyStickHat)
        {
            nameStream << "stick";
            if (base > 0)
            {
                nameStream << 1 + base;
            }
            nameStream << " " << 1 + (fromBase);
        }
        else
        {
            nameStream << "hat";
            if (base > 0)
            {
                nameStream << 1 + base;
            }
            nameStream << " ";
            switch (fromBase % 4)
            {
                case kKeyStickHatLeft:
                    nameStream << "left";
                    break;
                    
                case kKeyStickHatRight:
                    nameStream << "right";
                    break;
                    
                case kKeyStickHatUp:
                    nameStream << "up";
                    break;
                    
                case kKeyStickHatDown:
                    nameStream << "down";
                    break;
            }
        }
        retVal = nameStream.str();
    }
    return retVal;
}
