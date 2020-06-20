//%includeGuardStart {
#ifndef MEDIAKEYBOARD_H
#define MEDIAKEYBOARD_H
//%includeGuardStart } k7XHuyG8inwFEqkSEnMHLQ
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaKeyboard.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } mbFDRtsZlbukqnYifQ3aVA
/*
 * $Id: MediaKeyboard.h,v 1.5 2006/11/08 18:30:54 southa Exp $
 * $Log: MediaKeyboard.h,v $
 * Revision 1.5  2006/11/08 18:30:54  southa
 * Key and axis configuration
 *
 * Revision 1.4  2006/07/21 10:52:06  southa
 * win32 build fixes
 *
 * Revision 1.3  2006/07/11 19:49:05  southa
 * Control menu
 *
 * Revision 1.2  2006/07/08 16:05:57  southa
 * Ruby menus and key handling
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MediaStandard.h"

#include "SDL_keycode.h"


class MediaKeyboard
{
public:
    enum tKeySymbol {
        kKey_UNKNOWN=SDLK_UNKNOWN,
        kKey_BACKSPACE=SDLK_BACKSPACE,
        kKey_TAB=SDLK_TAB,
        kKey_CLEAR=SDLK_CLEAR,
        kKey_RETURN=SDLK_RETURN,
        kKey_PAUSE=SDLK_PAUSE,
        kKey_ESCAPE=SDLK_ESCAPE,
        kKey_SPACE=SDLK_SPACE,
        kKey_EXCLAIM=SDLK_EXCLAIM,
        kKey_QUOTEDBL=SDLK_QUOTEDBL,
        kKey_HASH=SDLK_HASH,
        kKey_DOLLAR=SDLK_DOLLAR,
        kKey_AMPERSAND=SDLK_AMPERSAND,
        kKey_QUOTE=SDLK_QUOTE,
        kKey_LEFTPAREN=SDLK_LEFTPAREN,
        kKey_RIGHTPAREN=SDLK_RIGHTPAREN,
        kKey_ASTERISK=SDLK_ASTERISK,
        kKey_PLUS=SDLK_PLUS,
        kKey_COMMA=SDLK_COMMA,
        kKey_MINUS=SDLK_MINUS,
        kKey_PERIOD=SDLK_PERIOD,
        kKey_SLASH=SDLK_SLASH,
        kKey_0=SDLK_0,
        kKey_1=SDLK_1,
        kKey_2=SDLK_2,
        kKey_3=SDLK_3,
        kKey_4=SDLK_4,
        kKey_5=SDLK_5,
        kKey_6=SDLK_6,
        kKey_7=SDLK_7,
        kKey_8=SDLK_8,
        kKey_9=SDLK_9,
        kKey_COLON=SDLK_COLON,
        kKey_SEMICOLON=SDLK_SEMICOLON,
        kKey_LESS=SDLK_LESS,
        kKey_EQUALS=SDLK_EQUALS,
        kKey_GREATER=SDLK_GREATER,
        kKey_QUESTION=SDLK_QUESTION,
        kKey_AT=SDLK_AT,
        kKey_LEFTBRACKET=SDLK_LEFTBRACKET,
        kKey_BACKSLASH=SDLK_BACKSLASH,
        kKey_RIGHTBRACKET=SDLK_RIGHTBRACKET,
        kKey_CARET=SDLK_CARET,
        kKey_UNDERSCORE=SDLK_UNDERSCORE,
        kKey_BACKQUOTE=SDLK_BACKQUOTE,
        kKey_a=SDLK_a,
        kKey_b=SDLK_b,
        kKey_c=SDLK_c,
        kKey_d=SDLK_d,
        kKey_e=SDLK_e,
        kKey_f=SDLK_f,
        kKey_g=SDLK_g,
        kKey_h=SDLK_h,
        kKey_i=SDLK_i,
        kKey_j=SDLK_j,
        kKey_k=SDLK_k,
        kKey_l=SDLK_l,
        kKey_m=SDLK_m,
        kKey_n=SDLK_n,
        kKey_o=SDLK_o,
        kKey_p=SDLK_p,
        kKey_q=SDLK_q,
        kKey_r=SDLK_r,
        kKey_s=SDLK_s,
        kKey_t=SDLK_t,
        kKey_u=SDLK_u,
        kKey_v=SDLK_v,
        kKey_w=SDLK_w,
        kKey_x=SDLK_x,
        kKey_y=SDLK_y,
        kKey_z=SDLK_z,
        kKey_DELETE=SDLK_DELETE,
        kKey_KP0=SDLK_KP_0,
        kKey_KP1=SDLK_KP_1,
        kKey_KP2=SDLK_KP_2,
        kKey_KP3=SDLK_KP_3,
        kKey_KP4=SDLK_KP_4,
        kKey_KP5=SDLK_KP_5,
        kKey_KP6=SDLK_KP_6,
        kKey_KP7=SDLK_KP_7,
        kKey_KP8=SDLK_KP_8,
        kKey_KP9=SDLK_KP_9,
        kKey_KP_PERIOD=SDLK_KP_PERIOD,
        kKey_KP_DIVIDE=SDLK_KP_DIVIDE,
        kKey_KP_MULTIPLY=SDLK_KP_MULTIPLY,
        kKey_KP_MINUS=SDLK_KP_MINUS,
        kKey_KP_PLUS=SDLK_KP_PLUS,
        kKey_KP_ENTER=SDLK_KP_ENTER,
        kKey_KP_EQUALS=SDLK_KP_EQUALS,
        kKey_UP=SDLK_UP,
        kKey_DOWN=SDLK_DOWN,
        kKey_RIGHT=SDLK_RIGHT,
        kKey_LEFT=SDLK_LEFT,
        kKey_INSERT=SDLK_INSERT,
        kKey_HOME=SDLK_HOME,
        kKey_END=SDLK_END,
        kKey_PAGEUP=SDLK_PAGEUP,
        kKey_PAGEDOWN=SDLK_PAGEDOWN,
        kKey_F1=SDLK_F1,
        kKey_F2=SDLK_F2,
        kKey_F3=SDLK_F3,
        kKey_F4=SDLK_F4,
        kKey_F5=SDLK_F5,
        kKey_F6=SDLK_F6,
        kKey_F7=SDLK_F7,
        kKey_F8=SDLK_F8,
        kKey_F9=SDLK_F9,
        kKey_F10=SDLK_F10,
        kKey_F11=SDLK_F11,
        kKey_F12=SDLK_F12,
        kKey_F13=SDLK_F13,
        kKey_F14=SDLK_F14,
        kKey_F15=SDLK_F15,
        kKey_NUMLOCK=SDLK_NUMLOCKCLEAR,
        kKey_CAPSLOCK=SDLK_CAPSLOCK,
        kKey_SCROLLOCK=SDLK_SCROLLLOCK,
        kKey_RSHIFT=SDLK_RSHIFT,
        kKey_LSHIFT=SDLK_LSHIFT,
        kKey_RCTRL=SDLK_RCTRL,
        kKey_LCTRL=SDLK_LCTRL,
        kKey_RALT=SDLK_RALT,
        kKey_LALT=SDLK_LALT,
        kKey_MODE=SDLK_MODE,
        kKey_HELP=SDLK_HELP,
        kKey_PRINT=SDLK_PRINTSCREEN,
        kKey_SYSREQ=SDLK_SYSREQ,
        kKey_MENU=SDLK_MENU,
        kKey_POWER=SDLK_POWER,
        kKey_UNDO=SDLK_UNDO,
        kKey_LAST,
        
        // Non-SDL key values 
        kKeyMouse0 = 1000,
        kKeyMouse1 = 1001,
        kKeyMouse2 = 1002,
        kKeyMouse3 = 1003,
        kKeyMouse4 = 1004,
        kKeyMouse5 = 1005,
        kKeyMouse6 = 1006,
        
        kKeyStickSpacing  = 100,
        kKeyStickHat      = 50,
        kKeyStickHatLeft  = 0,
        kKeyStickHatRight = 1,
        kKeyStickHatUp    = 2,
        kKeyStickHatDown  = 3,
         
        kKeyStick0   = 1200,
        kKeyStick0_0 = 1200,
        kKeyStick0_1 = 1201,
        kKeyStick0_2 = 1202,
        kKeyStick0_3 = 1203,
        
        kKeyStick1   = 1300,
        kKeyStick1_0 = 1300,
        kKeyStick1_1 = 1301,
        kKeyStick1_2 = 1302,
        kKeyStick1_3 = 1303,

        kKeyStick5   = 1700,
        
        kNumKeys
    };
    
    typedef enum {
        kMod_NONE  = 0x0000,
        kMod_LSHIFT= 0x0001,
        kMod_RSHIFT= 0x0002,
        kMod_LCTRL = 0x0040,
        kMod_RCTRL = 0x0080,
        kMod_LALT  = 0x0100,
        kMod_RALT  = 0x0200,
        kMod_LMETA = 0x0400,
        kMod_RMETA = 0x0800,
        kMod_NUM   = 0x1000,
        kMod_CAPS  = 0x2000,
        kMod_MODE  = 0x4000,
        kMod_RESERVED = 0x8000,
        
        kModShift = kMod_LSHIFT | kMod_RSHIFT,
        kModCtrl  = kMod_LCTRL  | kMod_RCTRL,
        kModAlt   = kMod_LALT   | kMod_RALT,
        kModMeta  = kMod_LMETA  | kMod_RMETA,
    } tKeyModifier;
    
    static std::string KeySymbolToName(Mushware::U32 keyValue);
    static bool HasModifier(Mushware::U32 inModifier, tKeyModifier inMask) { return (inModifier & inMask) != 0; }
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
