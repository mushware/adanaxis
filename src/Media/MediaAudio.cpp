/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: MediaAudio.cpp,v 1.13 2002/08/27 08:56:28 southa Exp $
 * $Log: MediaAudio.cpp,v $
 * Revision 1.13  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 */

#include "MediaAudio.h"
#include "MediaAudioSDL.h"
#include "MediaAudioNull.h"

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
