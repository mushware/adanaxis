/*
 * $Id: MediaAudio.h,v 1.1 2002/06/10 15:16:59 southa Exp $
 * $Log: MediaAudio.h,v $
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "MediaStandard.h"

class MediaAudio
{
public:
    static void Init();
    static void PlayMusic(const string& inName);

private:
    static bool m_audioGood;
};
