//%includeGuardStart {
#ifndef MUSHGAMERUBY_H
#define MUSHGAMERUBY_H
//%includeGuardStart } umLUrnBd0VXdkb0HFndGjw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRuby.h
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
//%Header } V/LeW1XSKW7vbJmo27mwng
/*
 * $Id: MushGameRuby.h,v 1.27 2007/06/30 11:45:44 southa Exp $
 * $Log: MushGameRuby.h,v $
 * Revision 1.27  2007/06/30 11:45:44  southa
 * X11 release
 *
 * Revision 1.26  2007/04/16 18:51:01  southa
 * Voice work
 *
 * Revision 1.25  2007/04/16 08:41:10  southa
 * Level and header mods
 *
 * Revision 1.24  2007/03/08 18:38:15  southa
 * Level progression
 *
 * Revision 1.23  2007/03/08 11:00:30  southa
 * Level epilogue
 *
 * Revision 1.22  2007/03/07 16:59:45  southa
 * Khazi spawning and level ends
 *
 * Revision 1.21  2006/12/11 18:54:19  southa
 * Positional audio
 *
 * Revision 1.20  2006/11/23 14:40:30  southa
 * Intro cutscene
 *
 * Revision 1.19  2006/11/21 16:13:55  southa
 * Cutscene handling
 *
 * Revision 1.18  2006/11/21 10:08:24  southa
 * Initial cut scene handling
 *
 * Revision 1.17  2006/11/08 18:30:54  southa
 * Key and axis configuration
 *
 * Revision 1.16  2006/10/16 22:00:21  southa
 * Tweaks
 *
 * Revision 1.15  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.14  2006/10/02 17:25:06  southa
 * Object lookup and target selection
 *
 * Revision 1.13  2006/09/29 10:47:56  southa
 * Object AI
 *
 * Revision 1.12  2006/08/01 13:41:15  southa
 * Pre-release updates
 *
 * Revision 1.11  2006/07/31 11:01:38  southa
 * Music and dialogues
 *
 * Revision 1.10  2006/07/28 16:52:24  southa
 * Options work
 *
 * Revision 1.9  2006/07/27 13:51:36  southa
 * Menu and control fixes
 *
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
    static Mushware::tRubyValue KeySymbolsToName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue GameModeEnter(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue MenuModeEnter(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue CutSceneModeEnter(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue CutSceneModeExit(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue NewGameEnter(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Quit(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue AxisName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue AxisSymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue AxisSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue AxisKeySymbols(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue AxisKeySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue KeySymbols(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
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
    static Mushware::tRubyValue VoiceVolume(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue VoiceVolumeSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue TextureDetail(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue TextureDetailSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue MouseSensitivity(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue MouseSensitivitySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue Brightness(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue BrightnessSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue ShowSubtitles(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue ShowSubtitlesSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue GameDialoguesLoad(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue NamedDialoguesAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue SoundDefine(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue SoundStreamDefine(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue SoundPlay(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue TiedSoundPlay(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue VoicePlay(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue SoundStreamPlay(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue PackageID(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue GameMsec(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue FreeMsec(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue PieceLookup(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue TargetPieceSelect(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2);
    static Mushware::tRubyValue EpilogueWon(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue EpilogueRunMsec(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue HelpFileOpen(Mushware::tRubyValue inSelf);
    
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
