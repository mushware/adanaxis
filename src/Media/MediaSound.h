#ifndef MEDIASOUND_H
#define MEDIASOUND_H
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
 * $Id: MediaSound.h,v 1.5 2002/08/27 08:56:28 southa Exp $
 * $Log: MediaSound.h,v $
 * Revision 1.5  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/24 13:12:32  southa
 * Null MediaAudio device
 *
 * Revision 1.3  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.2  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.1  2002/08/15 13:39:31  southa
 * CoreData and CoreDatRef
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaSound
{
public:
    MediaSound(const string& inName);
    ~MediaSound();
    void Load(void);
    void Free(void);
    void EndHandler(void);
    const string& FilenameGet(void) const { return m_filename; }
    Mix_Chunk *MixChunkGet(void) const { return m_chunk; }
    void MixChunkSet(Mix_Chunk *inChunk) { m_chunk=inChunk; }
    void ResidenceSet(bool inResident) { m_resident=inResident; }

    static CoreScalar TransientSound(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar ResidentSound(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar PlaySound(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);
    
private:
    string m_filename;
    Mix_Chunk *m_chunk;
    bool m_resident;
};
#endif
