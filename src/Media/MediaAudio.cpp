/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MediaAudio.cpp,v 1.17 2003/01/13 14:32:01 southa Exp $
 * $Log: MediaAudio.cpp,v $
 * Revision 1.17  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.16  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.15  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 */

#include "MediaAudio.h"
#include "MediaAudioNull.h"
#include "MediaAudioSDL.h"
#include "MediaSound.h"
#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MediaAudio);
MUSHCORE_DESTROY_SINGLETON_INSTANCE(MediaAudio);

MediaAudio::~MediaAudio()
{
    // Delete the MediaSound database before removing the audio services
    // that they're using
    if (MushcoreData<MediaSound>::SingletonExists())
    {
        MushcoreData<MediaSound>::SingletonDelete();
    }
}
