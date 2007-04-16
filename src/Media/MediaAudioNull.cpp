//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioNull.cpp
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
//%Header } 3Q7fcXztA5AKc5tr4IP2ng
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
