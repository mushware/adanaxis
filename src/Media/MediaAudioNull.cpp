//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioNull.cpp
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
//%Header } GC9fkeaRVVkgMxSrJQsZog
/*
 * $Id: MediaAudioNull.cpp,v 1.16 2006/12/11 18:54:18 southa Exp $
 * $Log: MediaAudioNull.cpp,v $
 * Revision 1.16  2006/12/11 18:54:18  southa
 * Positional audio
 *
 * Revision 1.15  2006/12/11 15:01:48  southa
 * Snapshot
 *
 * Revision 1.14  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:00  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.8  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.7  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.6  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 */

#include "MediaAudioNull.h"

#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

MediaAudioNull::MediaAudioNull()
{
}

void
MediaAudioNull::PlayMusic(const string& inName)
{
}

void
MediaAudioNull::Play(MediaSound& inSound)
{
}

void
MediaAudioNull::Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition,
                     Mushware::U32 inFlags)
{
}

void
MediaAudioNull::Play(MediaSoundStream& inSoundStream, U32 inLoop)
{
}

void
MediaAudioNull::VoicePlay(MediaSound& inSound)
{
}

void
MediaAudioNull::SoundHalt(MediaSound& inSound)
{
}

void
MediaAudioNull::Load(MediaSound& inSound) const
{
}

void
MediaAudioNull::Free(MediaSound& inSound) const
{
}

void
MediaAudioNull::Ticker(void)
{
}
