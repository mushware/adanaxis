#ifndef MEDIAAUDIO_H
#define MEDIAAUDIO_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: MediaAudio.h,v 1.6 2002/08/07 13:36:51 southa Exp $
 * $Log: MediaAudio.h,v $
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.2  2002/06/20 11:06:15  southa
 * Updated for cygwin
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "MediaStandard.h"

class MediaAudio
{
public:
    MediaAudio();
    ~MediaAudio();
    static MediaAudio& Instance(void) {return *((m_instance==NULL)?m_instance=new MediaAudio:m_instance);}
    void PlayMusic(const string& inName);
    void PlaySound(const string& inName);

private:
    static MediaAudio *m_instance;
};
#endif
