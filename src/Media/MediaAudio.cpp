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
 * $Id: MediaAudio.cpp,v 1.16 2002/12/29 20:59:58 southa Exp $
 * $Log: MediaAudio.cpp,v $
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

using namespace Mushware;
using namespace std;

auto_ptr<MediaAudio> MediaAudio::m_instance;

MediaAudio::~MediaAudio()
{
}

MediaAudio&
MediaAudio::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    InstanceCreate();
    return *m_instance;
}

void
MediaAudio::InstanceCreate()
{
    try
    {
        m_instance.reset(new MediaAudioSDL);
    }
    catch (exception& e)
    {
        cerr << "Exception creating MediaAudioSDL: " << e.what() << endl;
    }
    if (m_instance.get() == NULL)
    {
        m_instance.reset(new MediaAudioNull);
    }
}
