//%includeGuardStart {
#ifndef MEDIAKEYBOARD_H
#define MEDIAKEYBOARD_H
//%includeGuardStart } k7XHuyG8inwFEqkSEnMHLQ
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaKeyboard.h
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
//%Header } 8+s43zymtGuWatXc9oMynA
/*
 * $Id: MediaKeyboard.h,v 1.2 2006/07/08 16:05:57 southa Exp $
 * $Log: MediaKeyboard.h,v $
 * Revision 1.2  2006/07/08 16:05:57  southa
 * Ruby menus and key handling
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MediaStandard.h"

class MediaKeyboard
{
public:
    enum
    {
        kKey_UNKNOWN=0,
        kKey_FIRST=0,
        kKey_BACKSPACE=8,
        kKey_TAB=9,
        kKey_CLEAR=12,
        kKey_RETURN=13,
        kKey_PAUSE=19,
        kKey_ESCAPE=27,
        kKey_SPACE=32,
        kKey_EXCLAIM=33,
        kKey_QUOTEDBL=34,
        kKey_HASH=35,
        kKey_DOLLAR=36,
        kKey_AMPERSAND=38,
        kKey_QUOTE=39,
        kKey_LEFTPAREN=40,
        kKey_RIGHTPAREN=41,
        kKey_ASTERISK=42,
        kKey_PLUS=43,
        kKey_COMMA=44,
        kKey_MINUS=45,
        kKey_PERIOD=46,
        kKey_SLASH=47,
        kKey_0=48,
        kKey_1=49,
        kKey_2=50,
        kKey_3=51,
        kKey_4=52,
        kKey_5=53,
        kKey_6=54,
        kKey_7=55,
        kKey_8=56,
        kKey_9=57,
        kKey_COLON=58,
        kKey_SEMICOLON=59,
        kKey_LESS=60,
        kKey_EQUALS=61,
        kKey_GREATER=62,
        kKey_QUESTION=63,
        kKey_AT=64,
        kKey_LEFTBRACKET=91,
        kKey_BACKSLASH=92,
        kKey_RIGHTBRACKET=93,
        kKey_CARET=94,
        kKey_UNDERSCORE=95,
        kKey_BACKQUOTE=96,
        kKey_a=97,
        kKey_b=98,
        kKey_c=99,
        kKey_d=100,
        kKey_e=101,
        kKey_f=102,
        kKey_g=103,
        kKey_h=104,
        kKey_i=105,
        kKey_j=106,
        kKey_k=107,
        kKey_l=108,
        kKey_m=109,
        kKey_n=110,
        kKey_o=111,
        kKey_p=112,
        kKey_q=113,
        kKey_r=114,
        kKey_s=115,
        kKey_t=116,
        kKey_u=117,
        kKey_v=118,
        kKey_w=119,
        kKey_x=120,
        kKey_y=121,
        kKey_z=122,
        kKey_DELETE=127,
        kKey_WORLD_0=160,
        kKey_WORLD_1=161,
        kKey_WORLD_2=162,
        kKey_WORLD_3=163,
        kKey_WORLD_4=164,
        kKey_WORLD_5=165,
        kKey_WORLD_6=166,
        kKey_WORLD_7=167,
        kKey_WORLD_8=168,
        kKey_WORLD_9=169,
        kKey_WORLD_10=170,
        kKey_WORLD_11=171,
        kKey_WORLD_12=172,
        kKey_WORLD_13=173,
        kKey_WORLD_14=174,
        kKey_WORLD_15=175,
        kKey_WORLD_16=176,
        kKey_WORLD_17=177,
        kKey_WORLD_18=178,
        kKey_WORLD_19=179,
        kKey_WORLD_20=180,
        kKey_WORLD_21=181,
        kKey_WORLD_22=182,
        kKey_WORLD_23=183,
        kKey_WORLD_24=184,
        kKey_WORLD_25=185,
        kKey_WORLD_26=186,
        kKey_WORLD_27=187,
        kKey_WORLD_28=188,
        kKey_WORLD_29=189,
        kKey_WORLD_30=190,
        kKey_WORLD_31=191,
        kKey_WORLD_32=192,
        kKey_WORLD_33=193,
        kKey_WORLD_34=194,
        kKey_WORLD_35=195,
        kKey_WORLD_36=196,
        kKey_WORLD_37=197,
        kKey_WORLD_38=198,
        kKey_WORLD_39=199,
        kKey_WORLD_40=200,
        kKey_WORLD_41=201,
        kKey_WORLD_42=202,
        kKey_WORLD_43=203,
        kKey_WORLD_44=204,
        kKey_WORLD_45=205,
        kKey_WORLD_46=206,
        kKey_WORLD_47=207,
        kKey_WORLD_48=208,
        kKey_WORLD_49=209,
        kKey_WORLD_50=210,
        kKey_WORLD_51=211,
        kKey_WORLD_52=212,
        kKey_WORLD_53=213,
        kKey_WORLD_54=214,
        kKey_WORLD_55=215,
        kKey_WORLD_56=216,
        kKey_WORLD_57=217,
        kKey_WORLD_58=218,
        kKey_WORLD_59=219,
        kKey_WORLD_60=220,
        kKey_WORLD_61=221,
        kKey_WORLD_62=222,
        kKey_WORLD_63=223,
        kKey_WORLD_64=224,
        kKey_WORLD_65=225,
        kKey_WORLD_66=226,
        kKey_WORLD_67=227,
        kKey_WORLD_68=228,
        kKey_WORLD_69=229,
        kKey_WORLD_70=230,
        kKey_WORLD_71=231,
        kKey_WORLD_72=232,
        kKey_WORLD_73=233,
        kKey_WORLD_74=234,
        kKey_WORLD_75=235,
        kKey_WORLD_76=236,
        kKey_WORLD_77=237,
        kKey_WORLD_78=238,
        kKey_WORLD_79=239,
        kKey_WORLD_80=240,
        kKey_WORLD_81=241,
        kKey_WORLD_82=242,
        kKey_WORLD_83=243,
        kKey_WORLD_84=244,
        kKey_WORLD_85=245,
        kKey_WORLD_86=246,
        kKey_WORLD_87=247,
        kKey_WORLD_88=248,
        kKey_WORLD_89=249,
        kKey_WORLD_90=250,
        kKey_WORLD_91=251,
        kKey_WORLD_92=252,
        kKey_WORLD_93=253,
        kKey_WORLD_94=254,
        kKey_WORLD_95=255,
        kKey_KP0=256,
        kKey_KP1=257,
        kKey_KP2=258,
        kKey_KP3=259,
        kKey_KP4=260,
        kKey_KP5=261,
        kKey_KP6=262,
        kKey_KP7=263,
        kKey_KP8=264,
        kKey_KP9=265,
        kKey_KP_PERIOD=266,
        kKey_KP_DIVIDE=267,
        kKey_KP_MULTIPLY=268,
        kKey_KP_MINUS=269,
        kKey_KP_PLUS=270,
        kKey_KP_ENTER=271,
        kKey_KP_EQUALS=272,
        kKey_UP=273,
        kKey_DOWN=274,
        kKey_RIGHT=275,
        kKey_LEFT=276,
        kKey_INSERT=277,
        kKey_HOME=278,
        kKey_END=279,
        kKey_PAGEUP=280,
        kKey_PAGEDOWN=281,
        kKey_F1=282,
        kKey_F2=283,
        kKey_F3=284,
        kKey_F4=285,
        kKey_F5=286,
        kKey_F6=287,
        kKey_F7=288,
        kKey_F8=289,
        kKey_F9=290,
        kKey_F10=291,
        kKey_F11=292,
        kKey_F12=293,
        kKey_F13=294,
        kKey_F14=295,
        kKey_F15=296,
        kKey_NUMLOCK=300,
        kKey_CAPSLOCK=301,
        kKey_SCROLLOCK=302,
        kKey_RSHIFT=303,
        kKey_LSHIFT=304,
        kKey_RCTRL=305,
        kKey_LCTRL=306,
        kKey_RALT=307,
        kKey_LALT=308,
        kKey_RMETA=309,
        kKey_LMETA=310,
        kKey_LSUPER=311,
        kKey_RSUPER=312,
        kKey_MODE=313,
        kKey_COMPOSE=314,
        kKey_HELP=315,
        kKey_PRINT=316,
        kKey_SYSREQ=317,
        kKey_BREAK=318,
        kKey_MENU=319,
        kKey_POWER=320,
        kKey_EURO=321,
        kKey_UNDO=322,
        kKey_LAST,
        
        // Non-SDL key values 
        kKeyMouse0 = 1000,
        kKeyMouse1 = 1001,
        kKeyMouse2 = 1002,
        kKeyMouse3 = 1003,
        kKeyMouse4 = 1004,
        
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
    } tKeySymbol;
    
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