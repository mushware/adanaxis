//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioNull.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5Pij4hnOCd6ZWMxyVSMs8Q
/*
 * $Id: MediaAudioNull.cpp,v 1.10 2003/08/21 23:09:00 southa Exp $
 * $Log: MediaAudioNull.cpp,v $
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
MediaAudioNull::Play(MediaSoundStream& inSoundStream, U32 inLoop)
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
