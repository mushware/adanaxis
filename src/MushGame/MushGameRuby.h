//%includeGuardStart {
#ifndef MUSHGAMERUBY_H
#define MUSHGAMERUBY_H
//%includeGuardStart } umLUrnBd0VXdkb0HFndGjw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRuby.h
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
//%Header } abz8WfQdtsWpPxv12NZxhA
/*
 * $Id: MushGameRuby.h,v 1.8 2006/07/26 16:37:24 southa Exp $
 * $Log: MushGameRuby.h,v $
 * Revision 1.8  2006/07/26 16:37:24  southa
 * Options menu
 *
 * Revision 1.7  2006/07/12 11:22:43  southa
 * Advanced control menu
 *
 * Revision 1.6  2006/07/11 19:49:06  southa
 * Control menu
 *
 * Revision 1.5  2006/07/11 12:37:53  southa
 * Control configuration
 *
 * Revision 1.4  2006/07/10 16:01:19  southa
 * Control menu work
 *
 * Revision 1.3  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.2  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MushGameStandard.h"

#include "API/mushMushRuby.h"

class MushGameRuby : public MushRubyEmptyObj<4000>
{
public:
    static Mushware::tRubyValue KeySymbolToName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue GameModeEnter(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue NewGameEnter(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Quit(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue AxisName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue AxisSymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue AxisSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue AxisKeySymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue AxisKeySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue KeySymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue KeySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue NumJoysticks(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue ControlsToDefaultSet(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue DisplayModeString(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue PreviousDisplayMode(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue NextDisplayMode(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue DisplayReset(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue AudioVolume(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue AudioVolumeSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue MusicVolume(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue MusicVolumeSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue TextureDetail(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue TextureDetailSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);

    static void MethodsInstall(void);
    
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(4000)(void)
{
	EmptyInstallSubclass("MushGame", MushRubyObject::Klass());
    MushGameRuby::MethodsInstall();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
