//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudio.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } M5hw9KicfD7jNBbvZIKm4Q
/*
 * $Id: MediaAudio.cpp,v 1.23 2004/01/02 21:13:10 southa Exp $
 * $Log: MediaAudio.cpp,v $
 * Revision 1.23  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.22  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.21  2003/08/21 23:09:00  southa
 * Fixed file headers
 *
 * Revision 1.20  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.18  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
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
#include "MediaSTL.h"
#include "MediaSound.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MediaAudio);

MediaAudio::~MediaAudio()
{
    // Delete the MediaSound database before removing the audio services
    // that they're using
    MushcoreData<MediaSound>::SingletonDestroy();
}

MediaAudio *
MediaAudio::SingletonFactory(void)
{
    MediaAudio *pAudio;
    try
    {
        pAudio = new MediaAudioSDL;
    }
    catch (MushcoreNonFatalFail& e)
    {
        cerr << "Exception creating MediaAudioSDL: " << e.what() << endl;
        pAudio = new  MediaAudioNull;
    }
    return pAudio;
}
