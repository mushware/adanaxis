/*
 * $Id: MediaAudio.h,v 1.2 2002/06/20 11:06:15 southa Exp $
 * $Log: MediaAudio.h,v $
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

private:
    static MediaAudio *m_instance;
};
